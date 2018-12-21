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

    double A = 0;
    if (rank == 0)
        A = 3;
    if (rank == 1)
        A = 5;

    // MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Comm comm_cart;

    int ndims[] = {size / 2, 2};
    int periods[] = {0, 0};

    MPI_Cart_create(MPI_COMM_WORLD, 2, ndims, periods, 0, &comm_cart);

    int varying_coords[] = {1, 0};
    MPI_Comm comm_sub;
    MPI_Cart_sub(comm_cart, varying_coords, &comm_sub);
    MPI_Bcast(&A, 1, MPI_DOUBLE, 0, comm_sub);

    printf("rank%d A-%f\n", rank, A);

    MPI_Finalize();
    return 0;
}