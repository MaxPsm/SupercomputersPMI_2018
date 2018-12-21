#include <stdio.h>
#include <iostream>
#include <mpi.h>

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
    MPI_Status stat;

    int buf[size + 1];
    for (int i = 0; i < size + 1; ++i)
    {
        buf[i] = i + 10 * rank;
        printf("%d ", buf[i]);
    }
    printf("\n");
    int scounts[size], displs[size], rdispls[size];
    for (int i = 0; i < size; ++i)
    {
        scounts[i] = 2;
        displs[i] = i;
        rdispls[i] = 2 * i;
    }

    int dist[size + 1];
    MPI_Alltoallv(buf, scounts, displs, MPI_INT, dist, scounts, rdispls, MPI_INT, MPI_COMM_WORLD);

    for (int i = 0; i < size * 2; ++i)
        printf("%d ", dist[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}