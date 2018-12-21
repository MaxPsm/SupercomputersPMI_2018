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

    int buf[size + 2];
    for (int i = 0; i < size + 2; ++i)
        buf[i] = i;
    int dist[3];

    int scounts[size], displs[size];
    for (int i = 0; i < size; ++i)
    {
        scounts[i] = 3;
        displs[i] = i;
    }

    MPI_Scatterv(buf, scounts, displs, MPI_INT, dist, 3, MPI_INT, 0, MPI_COMM_WORLD);

    printf("rank %d: %d %d %d\n", rank, dist[0], dist[1], dist[2]);

    MPI_Finalize();
    return 0;
}