/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double *my_solver(int N, double *A, double *B) {
  printf("OPT SOLVER\n");
  register int i, j, k;
  double *A1;
  double *B1;

  double *ABB_tr;
  double *OUT;

  double *BB_tr;
  double *AA_tr;

  // allocate memory fro new matrix
  A1 = malloc(N * N * sizeof(*A1));
  B1 = malloc(N * N * sizeof(*B1));
  ABB_tr = malloc(N * N * sizeof(*ABB_tr));
  OUT = malloc(N * N * sizeof(*OUT));
  BB_tr = malloc(N * N * sizeof(*BB_tr));
  AA_tr = malloc(N * N * sizeof(*AA_tr));

  // AA_tr
  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = 0; k != N; ++k) {
  //       AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
  //     }
  //   }
  // }
  // try to optimize

  for (i = 0; i < N; i++) {
    register double *AA_tr_ptr = AA_tr + i * N;
    register double *A_cpy = A + i * N;

    for (j = 0; j < N; ++j, ++AA_tr_ptr) {
      register double res = 0;
      register double *A_ptr = A_cpy + i;
      register double *A_tr_ptr = A + i * N + j;
      for (k = 0; k <= i; ++k, ++A_ptr, A_tr_ptr += N) {
        // AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
        res += *A_ptr * *A_tr_ptr;
      }
      *A_tr_ptr += res;
    }
  }

  // BB_tr
  for (i = 0; i != N; ++i) {
    register double *BB_tr_ptr = BB_tr + i * N;
    register double *B_cpy = B + i * N;

    for (j = 0; j != N; ++j, ++BB_tr_ptr) {
      register double res = 0;

      register double *B_ptr = B_cpy;
      register double *B_tr_ptr = B + j * N;

      for (k = 0; k != N; ++k, ++B_ptr, ++B_tr_ptr) {
        res += *B_ptr * *B_tr_ptr;
      }
      *BB_tr_ptr = res;
    }
  }

  // ABB_tr
  //   for (i = 0; i != N; ++i) {
  //     register double *ABB_tr_ptr = ABB_tr + i * N;
  //     register double *A_cpy = A + i * N;

  //     for (j = 0; j != N; ++j, ++ABB_tr_ptr) {
  //       register double res = 0;
  //       register double *A_ptr = A_cpy + i;
  //       register double *BB_tr_ptr = BB_tr + i + j * N;

  //       for (k = i; k != N; ++k, ++A_ptr, ++BB_tr_ptr) {
  //         res += *A_ptr * *BB_tr_ptr;
  //       }
  //       *ABB_tr_ptr += res;
  //     }
  //   }

  for (i = 0; i != N; ++i) {
    register double *ABB_tr_ptr = ABB_tr + i * N;
    register double *A_cpy = A + i * N;

    for (j = 0; j != N; ++j, ++ABB_tr_ptr) {
      register double res = 0;
      register double *A_ptr = A_cpy + i;
      register double *BB_tr_ptr = BB_tr + i * N + j;

      for (k = i; k != N; ++k, ++A_ptr, BB_tr_ptr += N) {
        res += *A_ptr * *BB_tr_ptr;
      }
      *ABB_tr_ptr += res;
    }
  }

  // ABB_tr + AA_tr
  for (i = 0; i != N; ++i) {
    for (j = 0; j != N; ++j) {
      OUT[i * N + j] = ABB_tr[i * N + j] + AA_tr[i * N + j];
    }
  }

  free(ABB_tr);
  free(AA_tr);
  free(BB_tr);
  return OUT;
}
