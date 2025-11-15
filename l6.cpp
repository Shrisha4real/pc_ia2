
#include <mpi.h>
#include <iostream>

// Change this to 1 for deadlock, 2 for deadlock avoidance
#define DEADLOCK_PART 2

int main(int argc, char* argv[]) {
    int rank, size;
    int num = 123;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            std::cout << "Run with at least 2 processes.\n";
        MPI_Finalize();
        return 0;
    }

#if DEADLOCK_PART == 1
    // ----------- Part A: Deadlock -----------
    if (rank == 0) {
        std::cout << "Process 0 waiting to receive from Process 1...\n";
        MPI_Recv(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } 
    else if (rank == 1) {
        std::cout << "Process 1 waiting to receive from Process 0...\n";
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

#elif DEADLOCK_PART == 2
    // ----------- Part B: Deadlock Avoidance -----------
    if (rank == 0) {
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Process 0 received back number: " << num << std::endl;
    } 
    else if (rank == 1) {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        std::cout << "Process 1 received and sent back number: " << num << std::endl;
    }
#endif

    MPI_Finalize();
    return 0;
}
