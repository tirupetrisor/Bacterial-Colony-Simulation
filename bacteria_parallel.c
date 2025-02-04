#include "bacteria_parallel.h"


#define POLICY dynamic
#define CHUNKSIZE 20


/* Version 1: parallel for with scheduling policies and chunksizes */
void simulate_parallel_v1(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid)
{
    omp_set_num_threads(number_threads);  // Sets the number of threads
    for (int gen = 0; gen < generations; gen++)
    {
        // Apply the rules of the simulation
#pragma omp parallel for schedule(POLICY, CHUNKSIZE)
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                new_grid[i * COLS + j] = 0; // by default no bacterium

                int neighbors = count_neighbors(i, j, ROWS, COLS, grid);

                if (grid[i * COLS + j] == 1)
                { // If current cell has a bacterium
                    if (neighbors == 2 || neighbors == 3)
                        new_grid[i * COLS + j] = 1; // Survives in next generation
                }
                else
                { // If current cell is empty
                    if (neighbors == 3)
                        new_grid[i * COLS + j] = 1; // New bacterium appears here
                }
            }
        }
        // Make new grid to old grid for the next generation
        swap_ptr(&grid, &new_grid);

#ifdef DEBUG
        printf("After generation %d:\n", gen);
        print_grid(ROWS, COLS, grid);
#endif
    }
}


/* Version 2: parallel for with threads created only once in the beginning */
void simulate_parallel_v2(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid)
{
    omp_set_num_threads(number_threads);    // Sets the number of threads
#pragma omp parallel default(none) shared(generations, grid, new_grid, ROWS, COLS)
    for (int gen = 0; gen < generations; gen++)
    {
#pragma omp for
        // Apply the rules of the simulation
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
            {
                new_grid[i * COLS + j] = 0; // by default no bacterium

                int neighbors = count_neighbors(i, j, ROWS, COLS, grid);

                if (grid[i * COLS + j] == 1)
                { // If current cell has a bacterium
                    if (neighbors == 2 || neighbors == 3)
                        new_grid[i * COLS + j] = 1; // Survives in next generation
                }
                else
                { // If current cell is empty
                    if (neighbors == 3)
                        new_grid[i * COLS + j] = 1; // New bacterium appears here
                }
            }
        // Make new grid to old grid for the next generation
        // Ensure only one thread swaps the grids
#pragma omp single
        swap_ptr(&grid, &new_grid);
#ifdef DEBUG
#pragma omp single
        {
            printf("After generation %d:\n", gen);
            print_grid(ROWS, COLS, grid);
        }
#endif
    }
}


/* Version 3: manual explicit data partitioning */
void simulate_parallel_v3(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid)
{
    omp_set_num_threads(number_threads);   // Sets the number of threads
    for (int gen = 0; gen < generations; gen++) 
    {
#pragma omp parallel
        {
            int my_rank = omp_get_thread_num();        // Get the rank of the current thread
            int local_size = ROWS / number_threads;    // Calculate the number of rows each thread will process
            int remainder = ROWS % number_threads;     //Calculate how many extra rows are left if the number of threads is not divisible

            // Calculate the starting index for the current thread
            int start_index = my_rank * local_size;
            if (my_rank < remainder) 
            {
                start_index += my_rank;  
            } 
            else 
            {
                start_index += remainder; 
            }

            // Calculate the ending row index for the current thread
            int end_index = start_index + local_size - 1;
            if (my_rank < remainder) 
            {
                end_index += 1;
            }

            for (int i = start_index; i <= end_index; i++)
            {
                for (int j = 0; j < COLS; j++) 
                {
                    new_grid[i * COLS + j] = 0; // by default no bacterium

                    int neighbors = count_neighbors(i, j, ROWS, COLS, grid);

                    if (grid[i * COLS + j] == 1)
                    { // If current cell has a bacterium
                        if (neighbors == 2 || neighbors == 3)
                            new_grid[i * COLS + j] = 1; // Survives in next generation
                    }
                    else
                    { // If current cell is empty
                        if (neighbors == 3)
                            new_grid[i * COLS + j] = 1; // New bacterium appears here
                    }
                }
            }
        }
        // Make new grid to old grid for the next generation
        swap_ptr(&grid, &new_grid);
#ifdef DEBUG
        printf("After generation %d:\n", gen);
        print_grid(ROWS, COLS, grid);
#endif       
    }
}


void simulate_parallel_v4(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid)
{
    omp_set_num_threads(number_threads);   // Sets the number of threads
    for (int gen = 0; gen < generations; gen++) 
    {
#pragma omp parallel default(none) shared(generations, grid, new_grid, ROWS, COLS)
        {
#pragma omp single
            {
                // Divide the work into tasks for each row
                for (int i = 0; i < ROWS; i++) 
                {
#pragma omp task
                    {
                        for (int j = 0; j < COLS; j++) 
                        {
                           new_grid[i * COLS + j] = 0; // by default no bacterium

                            int neighbors = count_neighbors(i, j, ROWS, COLS, grid);

                            if (grid[i * COLS + j] == 1)
                            { // If current cell has a bacterium
                                if (neighbors == 2 || neighbors == 3)
                                    new_grid[i * COLS + j] = 1; // Survives in next generation
                            }
                            else
                            { // If current cell is empty
                                if (neighbors == 3)
                                    new_grid[i * COLS + j] = 1; // New bacterium appears here
                            }
                        }
                    }
                }
            }
        }
        // Make new grid to old grid for the next generation
        // Ensure only one thread swaps the grids
#pragma omp single
            swap_ptr(&grid, &new_grid);
#ifdef DEBUG
#pragma omp single
            {
                printf("After generation %d:\n", gen);
                print_grid(ROWS, COLS, grid);
            }
#endif
    }
}