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

    if (myRank == 0)
    {
        int n[4];
        for (int i = 1; i < size; ++i)
        {
            MPI_Recv(n, 4, MPI_INT, i, 0, MPI_COMM_WORLD, &stat);
            for (int i = 0; i < 4; ++i)
                cout << n[i] << " ";
            cout << endl;
        }
    }
    else
    {
        int n[4] = {1 + myRank, 2 + myRank, 3 + myRank, 4 + myRank};

        MPI_Send(n, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}