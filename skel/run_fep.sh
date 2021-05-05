#!/bin/bash

 module load compilers/gnu-5.4.0 
 make

 valgrind --tool=cachegrind --branch-sim=yes ./tema2_neopt /export/asc/tema2/input_valgrind 2> neopt.cache
 valgrind --tool=cachegrind --branch-sim=yes ./tema2_opt_m /export/asc/tema2/input_valgrind 2> opt_m.cache
 valgrind --tool=cachegrind --branch-sim=yes ./tema2_blas /export/asc/tema2/input_valgrind 2> blas.cache

 valgrind --tool=memcheck --leak-check=full ./tema2_neopt /export/asc/tema2/input_valgrind 2> neopt.memory
 valgrind --tool=memcheck --leak-check=full ./tema2_opt_m /export/asc/tema2/input_valgrind 2> opt_m.memory
 valgrind --tool=memcheck --leak-check=full ./tema2_blas /export/asc/tema2/input_valgrind 2> blas.memory

 ./tema2_blas input > blas.graf
 ./tema2_opt_m input > opt_m.graf
 ./tema2_neopt input > neopt.graf

 