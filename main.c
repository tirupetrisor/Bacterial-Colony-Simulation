#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "bacteria_utils.h"
#include "bacteria_serial.h"
#include "bacteria_parallel.h"

int main(int argc, char **argv) 
{
    // Check for correct number of command-line arguments
    if(argc != 4) 
    {
        fprintf(stderr, "Usage: %s <input_file> <number_of_generations> <number_of_threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    double start, run_time;
    double serial_time;

    const char *name_grid_file = argv[1];    // Input file with grid data
    int generations = atoi(argv[2]);        // Number of generations to simulate
    int number_threads = atoi(argv[3]);    // Number of threads for parallel execution

    int ROWS, COLS;
    int *grid = NULL;
    int *new_grid = NULL;
    int *serial_result = NULL;
    int version;

    // Allocate memory for output file names
    char *output_file_serial = malloc(strlen(name_grid_file) + 20);
    char *output_file_parallel = malloc(strlen(name_grid_file) + 30);

    /* Serial implementation */
    read_grid_from_file(name_grid_file, &grid, &new_grid, &ROWS, &COLS);  // Load the initial grid from the input file
    generate_output_file_serial(output_file_serial, name_grid_file);     // Generate a filename for serial output

    // Measure execution time for serial version
    start = omp_get_wtime();
    simulate_bacteria(generations, ROWS, COLS, grid, new_grid);
    run_time = omp_get_wtime() - start;
    serial_time = run_time;
    printf("Serial time version = %lf seconds\n", run_time);

    save_serial_result(&serial_result, ROWS, COLS, grid);     // Save serial result and output to file
    print_grid_to_file(serial_result, output_file_serial, ROWS, COLS);

    /* Parallel V1 implementation */
    version = 1;
    read_grid_from_file(name_grid_file, &grid, &new_grid, &ROWS, &COLS);      // Reinitialize the grid and new grid for parallel execution
    generate_output_file_parallel(output_file_parallel, name_grid_file, version);    // Generate a filename for parallel output (V2)

    // Measure execution time for parallel version 1
    start = omp_get_wtime();
    simulate_parallel_v1(number_threads, generations, ROWS, COLS, grid, new_grid);
    run_time = omp_get_wtime() - start;
    printf("\nParallel time V%d = %lf seconds\n", version, run_time);
    printf("Speedup V%d = %lf\n", version, serial_time/run_time);      // Calculate speedup for parallel version 1

    print_grid_to_file(grid, output_file_parallel, ROWS, COLS);     // Output the result of parallel version 1 to file
    validate_results(serial_result, grid, ROWS, COLS);    // Validate if parallel result matches the serial result
    
    /* Free grid memory after each version */
    free(grid);
    free(new_grid);

    /* Parallel V2 implementation */
    version = 2;
    read_grid_from_file(name_grid_file, &grid, &new_grid, &ROWS, &COLS);      // Reinitialize the grid and new grid for parallel execution
    generate_output_file_parallel(output_file_parallel, name_grid_file, version);    // Generate a filename for parallel output (V2)

    // Measure execution time for parallel version 2
    start = omp_get_wtime();
    simulate_parallel_v2(number_threads, generations, ROWS, COLS, grid, new_grid);
    run_time = omp_get_wtime() - start;
    printf("\nParallel time V%d = %lf seconds\n", version, run_time);
    printf("Speedup V%d = %lf\n", version, serial_time/run_time);     // Calculate speedup for parallel version 2

    print_grid_to_file(grid, output_file_parallel, ROWS, COLS);    // Output the result of parallel version 2 to file
    validate_results(serial_result, grid, ROWS, COLS);     // Validate if parallel result matches the serial result

    /* Free grid memory */
    free(grid);
    free(new_grid);

    /* Parallel V3 implementation */
    version = 3;
    read_grid_from_file(name_grid_file, &grid, &new_grid, &ROWS, &COLS);       // Reinitialize the grid and new grid for parallel execution
    generate_output_file_parallel(output_file_parallel, name_grid_file, version);    // Generate a filename for parallel output (V3)

    // Measure execution time for parallel version 3
    start = omp_get_wtime();
    simulate_parallel_v3(number_threads, generations, ROWS, COLS, grid, new_grid);
    run_time = omp_get_wtime() - start;
    printf("\nParallel time V%d = %lf seconds\n", version, run_time);
    printf("Speedup V%d = %lf\n", version, serial_time/run_time);        // Calculate speedup for parallel version 3

    print_grid_to_file(grid, output_file_parallel, ROWS, COLS);     // Output the result of parallel version 3 to file
    validate_results(serial_result, grid, ROWS, COLS);     // Validate if parallel result matches the serial result

    /* Free grid memory */
    free(grid);
    free(new_grid);

    /* Parallel V4 implementation */
    version = 4;
    read_grid_from_file(name_grid_file, &grid, &new_grid, &ROWS, &COLS);     // Reinitialize the grid and new grid for parallel execution
    generate_output_file_parallel(output_file_parallel, name_grid_file, version);    // Generate a filename for parallel output (V4)

    // Measure execution time for parallel version 4
    start = omp_get_wtime();
    simulate_parallel_v4(number_threads, generations, ROWS, COLS, grid, new_grid);
    run_time = omp_get_wtime() - start;
    printf("\nParallel time V%d = %lf seconds\n", version, run_time);
    printf("Speedup V%d = %lf\n", version, serial_time/run_time);     // Calculate speedup for parallel version 4

    print_grid_to_file(grid, output_file_parallel, ROWS, COLS);   // Output the result of parallel version 4 to file
    validate_results(serial_result, grid, ROWS, COLS);   // Validate if parallel result matches the serial result

    /* Free grid memory */
    free(grid);
    free(new_grid);

    /* Free allocated memory */
    free(output_file_parallel);
    free(serial_result);
    free(output_file_serial);

    return 0;
}
