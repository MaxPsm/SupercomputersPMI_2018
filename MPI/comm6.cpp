#include <stdio.h>
#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc, char *argv[])
{
    int errCode;
    MPI_Status status;
    if ((errCode = MPI_Init(&argc, &argv)) != 0)
    {
        return errCode;
    }

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm comm = MPI_COMM_NULL;

    int k = 0;
    int n = 0;
    if (rank == 0)
        k = size / 2;
    else
        n = rank % 2;

    double buf[k];

    for (int i = 0; i < k; ++i)
        buf[i] = rank % 2 ? 0 : 5;

    MPI_Comm_split(MPI_COMM_WORLD, rank % 2 ? MPI_UNDEFINED : 1, rank, &comm);

    double res;
    if (comm != MPI_COMM_NULL)
    {
        MPI_Scatter(buf, 1, MPI_DOUBLE, &res, 1, MPI_DOUBLE, 0, comm);
        MPI_Comm_free(&comm);
    }
    if (rank % 2 == 0)
        cout << res << endl;
    
    MPI_Finalize();
    return 0;
}