#include <stdio.h>
#include <iostream>
#include <mpi.h>

struct Data
{
    Data(int a, int b, double c) : a1(a), a2(b), a3(c) {}
    Data() {}
    int a1;
    int a2;
    double a3;
};

using namespace std;
int main(int argc, char *argv[])
{
    int errCode;

    if ((errCode = MPI_Init(&argc, &argv)) != 0)
    {
        return errCode;
    }

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype mytype;
    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_DOUBLE};
    int blocklen[3] = {1, 1, 1};
    Data buf[size - 1];
    MPI_Aint disp[3] = {0, sizeof(int), sizeof(int) + sizeof(int)};

    int position = 0;

    MPI_Type_create_struct(3, blocklen, disp, types, &mytype);
    MPI_Type_commit(&mytype);

    for (int i = 0; i < size - 1; ++i)
    {
        buf[i] = Data(i + 1, i + 1, i + 1);
    }

    Data outbuf[size];

    MPI_Pack(buf, size - 1, mytype, outbuf, sizeof(buf[0]) * (size - 1), &position, MPI_COMM_WORLD);
    MPI_Bcast(outbuf, position, MPI_PACKED, 0, MPI_COMM_WORLD);

    if (rank)
    {
        int pos = 0;
        MPI_Unpack(outbuf, sizeof(buf[0]) * (size - 1), &pos, buf, size - 1, mytype, MPI_COMM_WORLD);

        for (int i = 0; i < size - 1; ++i)
            printf("rank %d: %d %d %f\n", rank, buf[i].a1, buf[i].a2, buf[i].a3);
    }
    MPI_Finalize();
    return 0;
}