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
    MPI_Group group, newgroup;

    double buf[] = {1, 2};
    int sz = size % 2 == 0 ? size : size - 1;

    double src[sz];
    for (int i = 0; i < sz; ++i)
        src[i] = 0;
    int n = size - sz / 2;

    int ranks[n];
    for (int i = 0; i < n; ++i)
        ranks[i] = i * 2;

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    MPI_Group_excl(group, n, ranks, &newgroup);
    MPI_Comm_create(MPI_COMM_WORLD, newgroup, &comm);

    if (comm != MPI_COMM_NULL)
        MPI_Allgather(buf, 2, MPI_DOUBLE, src, 2, MPI_DOUBLE, comm);

    // cout << rank << endl;
    // if (rank % 2)
    for (int i = 0; i < sz; ++i)
        cout << src[i] << " ";
    cout << endl;
    MPI_Finalize();
    return 0;
}