#include <stdio.h>
#include <iostream>
#include <mpi.h>

void MPI_multiplication(double *in, double *inout, int *len, MPI_Datatype *dptr)
{
    for (int i = 0; i < *len; ++i)
    {
        *inout = *in * *inout;
        in++;
        inout++;
    }
}

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

    double A = rank;

    MPI_Comm comm_cart;

    int ndims[] = {2, 2, size / 4};
    int periods[] = {0, 0, 0};

    MPI_Cart_create(MPI_COMM_WORLD, 3, ndims, periods, 0, &comm_cart);

    int varying_coords[] = {1, 1, 0};
    MPI_Comm comm_sub;
    MPI_Cart_sub(comm_cart, varying_coords, &comm_sub);

    MPI_Op MPI_MUL;
    MPI_Op_create((MPI_User_function *)MPI_multiplication, true, &MPI_MUL);
    double res;

    MPI_Reduce(&A, &res, 1, MPI_DOUBLE, MPI_MUL, 0, comm_sub);

    MPI_Comm_rank(comm_sub, &rank);

    if (rank == 0)
        cout << res << endl;

    MPI_Finalize();
    return 0;
}