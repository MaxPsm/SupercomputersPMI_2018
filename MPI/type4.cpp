#include <stdio.h>
#include <iostream>
#include <mpi.h>

struct Data
{
    double a1;
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

    MPI_Datatype mytype;
    MPI_Datatype types[3] = {MPI_DOUBLE, MPI_INT, MPI_INT};
    int blocklen[3] = {1, 1, 1};
    Data buf;
    MPI_Aint disp[3] = {0, sizeof(double), sizeof(double) + sizeof(int)};

    MPI_Type_create_struct(3, blocklen, disp, types, &mytype);
    MPI_Type_commit(&mytype);

    buf.a1 = rank;
    buf.a2 = rank;
    buf.a3 = rank;

    Data dist[size];

    MPI_Gather(&buf, 1, mytype, &dist, 1, mytype, 0, MPI_COMM_WORLD);
    if (rank == 0)
        for (int i = 0; i < size; ++i)
            printf("rank %d: %f %d %d\n", rank, dist[i].a1, dist[i].a2, dist[i].a3);

    MPI_Finalize();
    return 0;
}