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

    if (myRank == 0)
    {
        double x;
        cin >> x;
        printf("-X=%f\n", -x);
    }
    else
        printf("rank %d\n", myRank);

    MPI_Finalize();
    return 0;
}