/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */

// C=A × B × Bt + At × A
double *my_solver(int N, double *A, double *B) {
  printf("NEOPT SOLVER\n");
  int i, j, k;
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
    for (j = 0; j < N; j++) {
      for (k = 0; k <= i; k++) {
        AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
      }
    }
  }

  // BB_tr
  for (i = 0; i != N; ++i) {
    for (j = 0; j != N; ++j) {
      for (k = 0; k != N; ++k) {
        BB_tr[i * N + j] += B[i * N + k] * B[j * N + k];
      }
    }
  }

  // ABB_tr
  for (i = 0; i != N; ++i) {
    for (j = 0; j != N; ++j) {
      for (k = i; k != N; ++k) {
        ABB_tr[i * N + j] += A[i * N + k] * BB_tr[k * N + j];
      }
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
