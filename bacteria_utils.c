#include "bacteria_utils.h"


/* Function for reading the grid dimensions and data from a file */
void read_grid_from_file(const char *grid_name, int **grid, int **new_grid, int *ROWS, int *COLS) 
{
    FILE *f_input = fopen(grid_name, "r");

    if(f_input == NULL) 
    {
        fprintf(stderr, "Failed to open the file");
        exit(EXIT_FAILURE);
    }

    // Read rows and columns from the file
    fscanf(f_input, "%d %d", ROWS, COLS);

    *grid = (int *)malloc((*ROWS) * (*COLS) * sizeof(int));
    if (!*grid) 
    {
        printf("Memory allocation error for grid\n");
        exit(1);
    }

    *new_grid = (int *)malloc((*ROWS) * (*COLS) * sizeof(int));
    if (!*new_grid) 
    {
        printf("Memory allocation error for new grid\n");
        exit(1);
    }

    // Read the grid values from the file: 'X' for a bacterium and '.' for an empty cell
    char read_variable;
    for (int i = 0; i < *ROWS; i++) 
    {
        for (int j = 0; j < *COLS; j++) 
        {
            fscanf(f_input, " %c", &read_variable);
            if(read_variable == 'X')
            {
                (*grid)[i * (*COLS) + j] = 1;    // Set 'X' as bacterium
            }
            else
            {
                (*grid)[i * (*COLS) + j] = 0;   // Set '.' as empty
            }
        }
    }

    if (fclose(f_input)) 
    {
        fprintf(stderr, "Failed to close the file");
        exit(EXIT_FAILURE);
    }
}


/* Function for writing the grid to a file */
void print_grid_to_file(int *grid, const char *filename, int ROWS, int COLS) 
{
    FILE *file = fopen(filename, "w");
    if (!file) 
    {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    // Write the grid to a file: 'X' for bacterium and '.' for empty cell
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            if(grid[i * COLS + j] == 1)
            {
                fprintf(file, "%c", 'X');   // Print 'X' for bacterium
            }
            else
            {
                fprintf(file, "%c", '.');   // Print '.' for empty cell
            }
        }
        fprintf(file, "\n");
    }

    if (fclose(file)) 
    {
        fprintf(stderr, "Failed to close the file");
        exit(EXIT_FAILURE);
    }
}


/* Function for printing the grid to the console */
void print_grid(int ROWS, int COLS, int *grid)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%c ", grid[i * COLS + j] ? 'X' : '.');  // Print 'X' for bacterium and '.' for empty cell on the console
        }
        printf("\n");
    }
}


/* Function for generating an output filename for the serial results based on the input filename */
void generate_output_file_serial(char *output_file, const char *input_file) 
{
    // Identify the extension point in the input file name
    const char *search_dot = strrchr(input_file, '.');

    // Copy the name up to the extension
    snprintf(output_file, search_dot - input_file + 1, "%s", input_file);
    strcat(output_file, "_serial_out.txt");
}


/* Function for generating an output filename for the parallel results based on the input filename and version */
void generate_output_file_parallel(char *output_file, const char *input_file, int version) 
{
    // Identify the extension point in the input file name
    const char *search_dot = strrchr(input_file, '.');

    // Copy the name up to the extension
    snprintf(output_file, search_dot - input_file + 1, "%s", input_file);
    sprintf(output_file + strlen(output_file), "_parallel_omp_V%d.txt", version);
}


/* Function for comparing the serial and parallel grids to check if the results match */
void validate_results(int *grid_serial, int *grid_parallel, int ROWS, int COLS)
{
    int verify = 1;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if(grid_serial[i * COLS + j] != grid_parallel[i * COLS +j])
            {
                verify = 0;    // Mark validation as failed
            }
        }
    }

    // Print validation result: check if the grids match
    if (verify == 1) 
    {
        printf("Validation successful: Parallel version matches serial result.\n");
    } 
    else 
    {
        printf("Validation failed: Parallel version does not match serial result.\n");
    }
}