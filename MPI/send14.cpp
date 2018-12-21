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

    int myRank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank = myRank;
    MPI_Status stat;

    printf("rank %d\n", myRank);
    srand(time(NULL));

    int dest1 = rank - 1;
    int dest2 = rank + 1;
    if (!rank)
        dest1 = size - 1;
    if (rank == size - 1)
        dest2 = 0;

    int ch;
    if (rank % 2)
    {
        MPI_Recv(&ch, 1, MPI_INT, dest1, 0, MPI_COMM_WORLD, &stat);
        MPI_Ssend(&rank, 1, MPI_INT, dest2, 0, MPI_COMM_WORLD);
        cout << ch << endl;
        MPI_Recv(&ch, 1, MPI_INT, dest2, 0, MPI_COMM_WORLD, &stat);
        MPI_Ssend(&rank, 1, MPI_INT, dest1, 0, MPI_COMM_WORLD);
        cout << ch << endl;
    }
    else
    {
        MPI_Ssend(&rank, 1, MPI_INT, dest2, 0, MPI_COMM_WORLD);
        MPI_Recv(&ch, 1, MPI_INT, dest1, 0, MPI_COMM_WORLD, &stat);
        cout << ch << endl;

        MPI_Ssend(&rank, 1, MPI_INT, dest1, 0, MPI_COMM_WORLD);
        MPI_Recv(&ch, 1, MPI_INT, dest2, 0, MPI_COMM_WORLD, &stat);
        cout << ch << endl;
    }

    MPI_Finalize();
    return 0;
}