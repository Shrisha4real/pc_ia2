
#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size;
    int number;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        number = 50;
        std::cout << "Process " << rank 
                  << " broadcasting number " << number 
                  << " to all other processes." << std::endl;
    }

    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::cout << "Process " << rank 
              << " received number " << number << std::endl;

    MPI_Finalize();
    return 0;
}
// to compile
// mpic++ -o broadcast l7.cpp:wq
