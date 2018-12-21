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

    MPI_Comm comm;

    MPI_Comm_split(MPI_COMM_WORLD, rank % 2, rank, &comm);

    double buf = rank;
    double res;
    if (rank % 2)
        MPI_Reduce(&buf, &res, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    else
        MPI_Reduce(&buf, &res, 1, MPI_DOUBLE, MPI_MIN, 1, comm);

    if (rank == 0)
        cout << res << endl;
    if (rank == 1)
        cout << res << endl;

    MPI_Comm_free(&comm);
    MPI_Finalize();
    return 0;
}