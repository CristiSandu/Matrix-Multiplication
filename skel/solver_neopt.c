/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"
#define MIN(x, y) ((x < y ? x : y))

/*
 * Add your unoptimized implementation here
 */

// C = A × B × Bt + At × A
double *my_solver(int N, double *A, double *B) {
  printf("NEOPT SOLVER\n");
  int i, j, k;

  double *ABB_tr;
  double *BB_tr;
  double *AA_tr;

  // allocate memory fro new matrix

  ABB_tr = malloc(N * N * sizeof(*ABB_tr));
  BB_tr = malloc(N * N * sizeof(*BB_tr));
  AA_tr = malloc(N * N * sizeof(*AA_tr));

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k <= MIN(i, j); k++) {
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
      ABB_tr[i * N + j] += AA_tr[i * N + j];
    }
  }

  free(AA_tr);
  free(BB_tr);
  return ABB_tr;
}
