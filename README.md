This project simulates the evolution of a bacteria colony using both serial and parallel versions. The simulation is implemented for different grid sizes and provides two modes of execution: interactive mode and normal mode (for performance measurements).

The program compares serial execution with four different parallel implementations using OpenMP, and provides a performance analysis through speedup calculations and graph generation.

Project Structure
The project is divided into the following source files:
-bacteria_utils.h and bacteria_utils.c: Handles file I/O for grid data, verifies parallel results against the serial version, and generates output file names with specific suffixes.
-bacteria_parallel.h and bacteria_parallel.c: Implements four different parallel versions of the bacteria colony simulation.
-bacteria_serial.h and bacteria_serial.c: Implements the sequential (serial) version of the bacteria colony simulation.
-main.c: The main program that simulates the evolution of the bacteria colony, compares the serial and parallel implementations, measures performance, and validates results.
-results_plots.xlsx: Contains the results from the simulation, including performance measurements for different numbers of threads, input files, and generations. The results also include speedup graphs.

To compile the project, use the following command: gcc -Wall -o prog main.c bacteria_utils.c bacteria_serial.c bacteria_parallel.c -fopenmp
For interactive (DEBUG) mode: gcc -Wall -o prog main.c bacteria_utils.c bacteria_serial.c bacteria_parallel.c -fopenmp -DDEBUG

To run the simulation, execute the compiled file with the following command: ./prog <input_file> <number_generations> <number_threads>
Where:
<input_file> is the path to the input file containing the initial grid configuration.
<number_generations> is the number of generations the simulation should run.
<number_threads> is the number of threads to use for parallel execution.
