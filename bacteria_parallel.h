#ifndef _BACTERIA_PARALLEL_H
#define _BACTERIA_PARALLEL_H


#include <stdio.h>
#include <omp.h>
#include "bacteria_serial.h"
#include "bacteria_utils.h"


void simulate_parallel_v1(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid);
void simulate_parallel_v2(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid);
void simulate_parallel_v3(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid);
void simulate_parallel_v4(int number_threads, int generations, int ROWS, int COLS, int *grid, int *new_grid);


#endif