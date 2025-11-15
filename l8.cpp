#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Use std::vector for automatic memory management
    std::vector<int> send_data(size, 0);
    int recv_data = 0;
    std::vector<int> gathered_data(size, 0);

    // Only root (rank 0) initializes send_data
    if (rank == 0) {
        for (int i = 0; i < size; ++i) {
            send_data[i] = i * 10;
        }
        std::cout << "Root process sending: ";
        for (int i = 0; i < size; ++i) {
            std::cout << send_data[i] << " ";
        }
        std::cout << "\n";
    }

    // Scatter: send 1 int from root to each process
    MPI_Scatter(send_data.data(), 1, MPI_INT,
                &recv_data,       1, MPI_INT,
                0, MPI_COMM_WORLD);

    // Each process modifies its received value
    recv_data = recv_data + rank;

    std::cout << "Process " << rank << " received " << (recv_data - rank)
              << ", added rank → now " << recv_data << "\n";

    // Gather: collect modified values back to root
    MPI_Gather(&recv_data, 1, MPI_INT,
               gathered_data.data(), 1, MPI_INT,
               0, MPI_COMM_WORLD);

    // Only root prints final gathered data
    if (rank == 0) {
        std::cout << "\nGathered data in root process:\n";
        for (int i = 0; i < size; ++i) {
            std::cout << "gathered_data[" << i << "] = " << gathered_data[i] << "\n";
        }
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
// compile mpic++ -o l8 l8.cpp
//
// run mpirun -np 4 ./l8 
