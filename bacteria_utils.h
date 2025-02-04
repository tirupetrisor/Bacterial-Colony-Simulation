#ifndef _BACTERIA_UTILS_H
#define _BACTERIA_UTILS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bacteria_serial.h"


void read_grid_from_file(const char *grid_name, int **grid, int **new_grid, int *ROWS, int *COLS);
void print_grid_to_file(int *grid, const char *filename, int ROWS, int COLS);
void print_grid(int ROWS, int COLS, int *grid);
void generate_output_file_serial(char *output_file, const char *input_file);
void generate_output_file_parallel(char *output_file, const char *input_file, int version);
void validate_results(int *grid_serial, int *grid_parallel, int ROWS, int COLS);


#endif