#ifndef _BACTERIA_SERIAL_H
#define _BACTERIA_SERIAL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bacteria_utils.h"


void swap_ptr(int **p1, int **p2);
int count_neighbors(int x, int y, int ROWS, int COLS, int *grid);
void simulate_bacteria(int generations, int ROWS, int COLS, int *grid, int *new_grid);
void save_serial_result(int **serial_result, int ROWS, int COLS, int *grid);

#endif