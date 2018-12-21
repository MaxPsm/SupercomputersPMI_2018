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

    if (myRank == 0)
    {
        double n[size];
        for (int i = 1; i < size; ++i)
        {
            n[i - 1] = i;
            MPI_Send(&n[i - 1], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        double ch;

        MPI_Recv(&ch, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &stat);
        cout << ch << endl;
    }

    MPI_Finalize();
    return 0;
}