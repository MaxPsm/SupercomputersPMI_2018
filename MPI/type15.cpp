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

    int k = size - 1;
    MPI_Datatype mytype;

    if (rank == 0)
    {
        MPI_Type_create_resized(MPI_DOUBLE, 0, sizeof(double) * k, &mytype);
        MPI_Type_commit(&mytype);

        double A[k * k];
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < k; ++j)
                A[k * i + j] = j;

        for (int i = 0; i < k * k; ++i)
            A[i] = i;

        // for (int i = 0; i < k; ++i)
        // {
        //     for (int j = 0; j < k; ++j)
        //         cout << A[k * i + j];
        //     cout << endl;
        // }
        // cout << endl;

        for (int i = 0; i < k; ++i)
        {
            MPI_Send(A + i, k, mytype, i + 1, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        double buf[k];

        MPI_Recv(buf, k, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < k; ++i)
            cout << buf[i] << " ";
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}