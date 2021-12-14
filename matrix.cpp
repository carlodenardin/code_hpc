#include <iostream>
#include <string>
#include "mpi.h"

int main(int argc, char **argv) {
    int rank, size;
    double time, maxtime, mintime, avgtime;
    MPI_Status status;

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    int x = std::stoi(argv[1]);
    int y = std::stoi(argv[2]);
    int z = std::stoi(argv[3]);

    int x_small = std::stoi(argv[4]);
    int y_small = std::stoi(argv[5]);
    int z_small = std::stoi(argv[6]);

    double* matrix_1 = new double[x * y * z];
    double* matrix_2 = new double[x * y * z];
    double* matrix_3 = new double[x * y * z];
    double* matrix_1_small = new double[x_small * y_small * z_small];
    double* matrix_2_small = new double[x_small * y_small * z_small];
    double* matrix_3_small = new double[x_small * y_small * z_small];

    int elements_small_matrix = x_small * y_small * z_small;

    if (rank == 0) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    *(matrix_1 + i * y * z + j * z + k) = (double)rand() / RAND_MAX * 100;
                    *(matrix_2 + i * y * z + j * z + k) = (double)rand() / RAND_MAX * 100;
                }
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    time = MPI_Wtime();

    MPI_Scatter(matrix_1, elements_small_matrix, MPI_DOUBLE, matrix_1_small, elements_small_matrix, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrix_2, elements_small_matrix, MPI_DOUBLE, matrix_2_small, elements_small_matrix, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < x_small; i++) {
        for (int j = 0; j < y_small; j++) {
            for (int k = 0; k < z_small; k++) {
                *(matrix_3_small + i * y_small * z_small + j * z_small + k) = *(matrix_1_small + i * y_small * z_small + j * z_small + k) + *(matrix_2_small + i * y_small * z_small + j * z_small + k);
            }
        }
    }

    MPI_Gather(matrix_3_small, elements_small_matrix, MPI_DOUBLE, matrix_3, elements_small_matrix, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    time = MPI_Wtime() - time;

    MPI_Reduce(&time, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&time, &mintime, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&time, &avgtime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        float sum1 = 0;
        float sum2 = 0;
        float sum3 = 0;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    sum1 = sum1 + *(matrix_1 + i * y * z + j * z + k);
                    sum2 = sum2 + *(matrix_2 + i * y * z + j * z + k);
                    sum3 = sum3 + *(matrix_3 + i * y * z + j * z + k);
                }
            }
        }
        avgtime = avgtime / size;
        std::cout << "[" << x << ", " << y << ", " << z << "] ---> " << 24 << "*[" << x_small << ", " << y_small << ", " << z_small << "]" << std::endl;
        std::cout << "MAX: " << maxtime << " MIN: " << mintime << " AVG: " << avgtime << std::endl;
        std::cout << "SUM M1: " << sum1 << "\nSUM M2: " << sum2 << "\nSUM M1 + M2: " << sum3 << std::endl;
    }

    delete[] matrix_1;
    delete[] matrix_2;
    delete[] matrix_3;
    delete[] matrix_1_small;
    delete[] matrix_2_small;
    delete[] matrix_3_small;

    MPI_Finalize();

    return 0;
}