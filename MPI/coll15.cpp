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
;
    int buf[size*3];
    for (int i = 0; i < size*3; ++i)
        buf[i] = i + 10 * rank;

    int dist[size*3];
    MPI_Alltoall(buf,3,MPI_INT,dist,3,MPI_INT,MPI_COMM_WORLD);

    for (int i = 0; i < size*3; ++i)
        printf("%d ", dist[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}