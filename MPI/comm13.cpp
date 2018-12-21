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
    
    int n = 0;
    if (!rank)
        n = 2;

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Comm comm_cart;

    int ndims[] = {n, size / n};
    int periods[] = {0, 0};

    MPI_Cart_create(MPI_COMM_WORLD, 2, ndims, periods, 0, &comm_cart);

    int coords[2];
    MPI_Cart_coords(comm_cart, rank, 2, coords);

    printf("rank%d (%d;%d)\n", rank, coords[0], coords[1]);

    MPI_Finalize();
    return 0;
}