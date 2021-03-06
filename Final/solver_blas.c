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
        B*B_t = DGEMM nu este triunghiulara
        A*BB_t = DTRMM A este triunghoulara
        A_t*A = DTRMM At*A este triunghiulara
  */

  double *BB_tr;
  double *ABB_tr;
  double *AA_tr;
  int i, j;

  ABB_tr = malloc(N * N * sizeof(*ABB_tr));
  BB_tr = malloc(N * N * sizeof(*BB_tr));
  AA_tr = malloc(N * N * sizeof(*AA_tr));

  // B*Bt
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, B, N, B, N,
              0.0, BB_tr, N);

  // A*BB_t
  memcpy(ABB_tr, BB_tr, N * N * sizeof(*ABB_tr));
  cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit,
              N, N, 1.0, A, N, ABB_tr, N);

  // A_t*A
  memcpy(AA_tr, A, N * N * sizeof(*AA_tr));
  cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N,
              N, 1.0, A, N, AA_tr, N);

  // ABB_t + AA_t
  for (i = 0; i != N; i++)
    for (j = 0; j != N; j++)
      ABB_tr[i * N + j] += AA_tr[i * N + j];

  free(AA_tr);
  free(BB_tr);

  return ABB_tr;
}