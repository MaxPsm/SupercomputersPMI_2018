#include <stdio.h>
#include <iostream>
#include <mpi.h>

struct Data
{
    int a1;
    int a2;
    int a3;
};

using namespace std;
int main(int argc, char *argv[])
{
    int errCode;

    if ((errCode = MPI_Init(&argc, &argv)) != 0)
    {
        return errCode;
    }

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype type;
    MPI_Type_contiguous(3, MPI_INT, &type);

    MPI_Type_commit(&type);

    Data buf[size - 1];
    for (int i = 0; i < size - 1; ++i)
    {
        buf[i].a1 = i;
        buf[i].a3 = i;
        buf[i].a2 = i;
    }
    Data dist;
    int scounts[size], displs[size];
    for (int i = 0; i < size; ++i)
    {
        scounts[i + 1] = 1;
        displs[i + 1] = i;
    }
    scounts[0] = displs[0] = 0;

    MPI_Scatterv(buf, scounts, displs, type, &dist, 1, type, 0, MPI_COMM_WORLD);
    if (rank)
        printf("rank %d: %d %d %d\n", rank, dist.a1, dist.a2, dist.a3);

    MPI_Finalize();
    return 0;
}