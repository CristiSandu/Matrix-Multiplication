/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "cblas.h"
#include "utils.h"
#include <string.h>
/*
 * Add your BLAS implementation here
 */
double *my_solver(int N, double *A, double *B) {
  printf("BLAS SOLVER\n");

  /*
        // C=A × B × Bt + At × A
        B*B_t = DGEMM
        A*BB_T = DTRMM
        At*A = DTRMM
  */

  double *BB_tr;
  double *ABB_tr;
  double *AA_tr;
  double *OUT;

  ABB_tr = malloc(N * N * sizeof(*ABB_tr));
  BB_tr = malloc(N * N * sizeof(*BB_tr));
  AA_tr = malloc(N * N * sizeof(*AA_tr));
  OUT = malloc(N * N * sizeof(*OUT));

  memcpy(BB_tr, B, N * N * sizeof(*BB_tr));
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, B, N, B, N,
              0.0, BB_tr, N);
  return BB_tr;
}

/*
 a = [0.11 0.12 0.13;
      0.21 0.22 0.23]
b = [1011 1012;
        1021 1022;
        1031 1032 ]
*/