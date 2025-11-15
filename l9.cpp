
#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size;
    int value, sum, prod, max, min;
    int all_sum, all_prod, all_max, all_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    value = rank + 1;

    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "--- Results using MPI_Reduce (only root prints) ---\n";
        std::cout << "Sum = " << sum << std::endl;
        std::cout << "Product = " << prod << std::endl;
        std::cout << "Max = " << max << std::endl;
        std::cout << "Min = " << min << std::endl;
    }

    std::cout << "Process " << rank << " sees (MPI_Allreduce results):\n";
    std::cout << "  Sum = " << all_sum 
              << ", Product = " << all_prod
              << ", Max = " << all_max
              << ", Min = " << all_min 
              << std::endl;

    MPI_Finalize();
    return 0;
}
