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

    int rank, size, comm_size = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm comm = MPI_COMM_NULL;

    MPI_Comm_split(MPI_COMM_WORLD, rank % 2 ? 1 : 2, rank, &comm);

    MPI_Comm_size(comm, &comm_size);

    double get[comm_size];
    double send = rank;

    MPI_Allgather(&send, 1, MPI_DOUBLE, get, 1, MPI_DOUBLE, comm);

    for (int i = 0; i < comm_size; ++i)
        cout << get[i];
    cout << endl;

    if (comm != MPI_COMM_NULL)
        MPI_Comm_free(&comm);
    MPI_Finalize();
    return 0;
}