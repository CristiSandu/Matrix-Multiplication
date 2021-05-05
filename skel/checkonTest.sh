#!/bin/bash

 module load compilers/gnu-5.4.0 
 make

 ./tema2_neopt /export/asc/tema2/input > timeNeopt
 ./compare out1 /export/asc/tema2/out1 0.001 >> timeNeopt
 ./compare out2 /export/asc/tema2/out2 0.001 >> timeNeopt
 ./compare out3 /export/asc/tema2/out3 0.001 >> timeNeopt

 ./tema2_opt_m /export/asc/tema2/input > timeOpt
 ./compare out1 /export/asc/tema2/out1 0.001 >> timeOpt
 ./compare out2 /export/asc/tema2/out2 0.001 >> timeOpt
 ./compare out3 /export/asc/tema2/out3 0.001 >> timeOpt

 ./tema2_blas /export/asc/tema2/input > timeBlas
 ./compare out1 /export/asc/tema2/out1 0.001 >> timeBlas
 ./compare out2 /export/asc/tema2/out2 0.001 >> timeBlas
 ./compare out3 /export/asc/tema2/out3 0.001 >> timeBlas