#include "bacteria_serial.h"


/* Used to swap grids between generations */
void swap_ptr(int **p1, int **p2)
{
    int *tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}



/* Count alive neighbours of (x,y) in grid */
int count_neighbors(int x, int y, int ROWS, int COLS, int *grid)
{
    int count = 0;
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 && dy != 0)
            { // count only neighbours, not current cell
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS)
                {
                    if (grid[nx * COLS + ny] == 1)
                        count++;
                }
            }
        }

    return count;
}

/* Serial version for implementing the simulation of bacterial evolution */
void simulate_bacteria(int generations, int ROWS, int COLS, int *grid, int *new_grid)
{
    for (int gen = 0; gen < generations; gen++)
    {
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
        swap_ptr(&grid, &new_grid);
#ifdef DEBUG
        printf("After generation %d:\n", gen);
        print_grid(ROWS, COLS, grid);
#endif
    }
}


/* Copies the final state of the grid into a separate memory block, without modifying the original simulation data */
void save_serial_result(int **serial_result, int ROWS, int COLS, int *grid)
{
    *serial_result = (int *)malloc(ROWS * COLS * sizeof(int));
    if (!*serial_result) {
        printf("Memory allocation error for serial result\n");
        exit(1);
    }

    //Copy the contents of the current grid to the serial result
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            (*serial_result)[i * COLS + j] = grid[i * COLS + j];
        }
    }
}
