#include "cblas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MIN(a, b) ((a < b ? a : b))
#define MAX(a, b) ((a > b ? a : b))

int main(int argc, char const *argv[]) {

  int N = 6;
  double *A;
  double *B;
  register int i, k, j;

  int numMatrixElems = N * N;
  A = malloc(numMatrixElems * sizeof(*A));
  B = malloc(numMatrixElems * sizeof(*B));
  int nr = 0, nr2 = 9;
  for (i = 0; i != N; ++i) {
    for (j = i; j != N; ++j) {
      A[i * N + j] = nr;
      nr++;
    }
    for (j = 0; j != N; ++j) {
      B[i * N + j] = nr2;
      nr2++;
    }
  }

  double *AA_tr;
  AA_tr = malloc(numMatrixElems * sizeof(*AA_tr));

  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = 0; k != N; ++k) {
  //       AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
  //       // AA_tr[i * N + j] += B[i * N + k] * A[j * N + k];
  //     }
  //   }
  // }

  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = 0; k != N; ++k) {
  //       AA_tr[i * N + j] += B[i * N + k] * B[j * N + k];
  //     }
  //   }
  // }

  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = i; k != N; ++k) {
  //       AA_tr[i * N + j] += A[i * N + k] * B[k * N + j];
  //     }
  //   }
  // }

  // for (i = 0; i < N; i++) {
  //   for (j = 0; j < N; j++) {
  //     for (k = 0; k <= i; k++) {
  //       AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
  //     }
  //   }
  // }

  // double *A1;
  // double *B1;

  // double *ABB_tr;
  // double *OUT;

  // double *BB_tr;

  // // allocate memory fro new matrix
  // A1 = malloc(N * N * sizeof(*A1));
  // B1 = malloc(N * N * sizeof(*B1));
  // ABB_tr = malloc(N * N * sizeof(*ABB_tr));
  // OUT = malloc(N * N * sizeof(*OUT));
  // BB_tr = malloc(N * N * sizeof(*BB_tr));
  // AA_tr = malloc(N * N * sizeof(*AA_tr));

  // // AA_tr
  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = 0; k != N; ++k) {
  //       AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
  //     }
  //   }
  // }
  // // try to optimize
  // /*  for (i = 0; i < N; i++) {
  //     for (j = 0; j < N; j++) {
  //       for (k = 0; k <= i; k++) {
  //         AA_tr[i * N + j] += A[k * N + i] * A[k * N + j];
  //       }
  //     }
  //   }*/

  // // BB_tr
  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = 0; k != N; ++k) {
  //       BB_tr[i * N + j] += B[i * N + k] * B[j * N + k];
  //     }
  //   }
  // }

  // // ABB_tr
  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     for (k = i; k != N; ++k) {
  //       ABB_tr[i * N + j] += A[i * N + k] * BB_tr[k * N + j];
  //     }
  //   }
  // }

  // // ABB_tr + AA_tr
  // for (i = 0; i != N; ++i) {
  //   for (j = 0; j != N; ++j) {
  //     OUT[i * N + j] = ABB_tr[i * N + j] + AA_tr[i * N + j];
  //   }
  // }
  double *BB_tr;
  double *ABB_tr;
  double *OUT;

  ABB_tr = malloc(N * N * sizeof(*ABB_tr));
  BB_tr = malloc(N * N * sizeof(*BB_tr));
  AA_tr = malloc(N * N * sizeof(*AA_tr));
  OUT = malloc(N * N * sizeof(*OUT));

  /*memcpy(BB_tr, B, N * N * sizeof(*BB_tr));
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, B, N, B, N,
              0.0, BB_tr, N);*/
  // memcpy(ABB_tr, A, N * N * sizeof(*ABB_tr));
  // cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans,
  // CblasNonUnit,
  //             N, N, 1.0, ABB_tr, N, B, N);

  // memcpy(AA_tr, A, N * N * sizeof(*AA_tr));
  // cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit,
  // N,
  //             N, 1.0, A, N, AA_tr, N);

  // for (i = 0; i != N; ++i) {
  //   register double *BB_tr_ptr = BB_tr + i * N;
  //   register double *B_cpy = B + i * N;

  //   for (j = 0; j != N; ++j, ++BB_tr_ptr) {
  //     register double res = 0;

  //     register double *B_ptr = B_cpy;
  //     register double *B_tr_ptr = B + j * N;

  //     for (k = 0; k != N; ++k, ++B_ptr, ++B_tr_ptr) {
  //       res += *B_ptr * *B_tr_ptr;
  //     }
  //     *BB_tr_ptr = res;
  //   }
  // }
  // memcpy(BB_tr, B, N * N * sizeof(*BB_tr));

  // for (i = 0; i != N; ++i) {
  //   register double *ABB_tr_ptr = ABB_tr + i * N;
  //   register double *A_cpy = A + i * N;

  //   for (j = 0; j != N; ++j, ++ABB_tr_ptr) {
  //     register double res = 0;
  //     register double *A_ptr = A_cpy + i;
  //     register double *BB_tr_ptr = BB_tr + i * N + j;

  //     for (k = i; k != N; ++k, ++A_ptr, BB_tr_ptr += N) {
  //       res += *A_ptr * *BB_tr_ptr;
  //     }
  //     *ABB_tr_ptr += res;
  //   }
  // }

  // for (i = 0; i < N; ++i) {
  //   register double *AA_tr_ptr = AA_tr + i * N;
  //   register double *A_cpy = A + i * N;

  //   for (j = 0; j < N; ++j, ++AA_tr_ptr) {
  //     register double res = 0;
  //     register double *A_ptr = A_cpy + i;
  //     register double *A_tr_ptr = A + i * N + j;
  //     for (k = 0; k <= MIN(i, j); ++k, ++A_ptr, A_tr_ptr += N) {
  //       res += *A_tr_ptr * *A_ptr;
  //     }
  //     *AA_tr_ptr += res;
  //   }
  // }

  for (i = 0; i < N; ++i) {
    register double *AA_tr_ptr = AA_tr + i * N;
    for (j = 0; j < N; ++j, ++AA_tr_ptr) {
      register double res = 0;
      for (k = 0; k <= MIN(i, j); ++k) {
        res += A[k * N + i] * A[k * N + j];
      }
      *AA_tr_ptr += res;
    }
  }
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      printf("%f  ", A[i * N + j]);
    }
    printf("\n");
  }
  printf("\n");

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      printf("%f  ", B[i * N + j]);
    }
    printf("\n");
  }
  printf("\n");

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      printf("%f ", AA_tr[i * N + j]);
    }
    printf("\n");
  }

  return 0;
}
/*
A = [0.680375 0.566198 0.823295 -0.329554 -0.444451 -0.045206;
     0 0.904459 0.271423 -0.716795 -0.967399 -0.725537;
     0 0 0.997849 0.025865 0.225280 0.275105;
     0 0 0 -0.199543 -0.433371 0.615449; 0 0 0 0 -0.871657 -0.084597;
     0 0 0 0 0 0.063213]*/

/*A = [0.000000  1.000000  2.000000  3.000000  4.000000  5.000000;
0  7.000000  8.000000  9.000000  10.000000  11.000000;
0  0  14.000000  15.000000  16.000000  17.000000;
0  0  0  21.000000  22.000000  23.000000;
0  0  0  0  28.000000  29.000000;
0  0  0  0  0  35.000000]  */

/*a = [0.000000 1.000000 2.000000 3.000000 4.000000 5.000000;
     0.000000 6.000000 7.000000 8.000000 9.000000 10.000000;
     0.000000 0.000000 11.000000 12.000000 13.000000 14.000000;
     0.000000 0.000000 0.000000 15.000000 16.000000 17.000000;
     0.000000 0.000000 0.000000 0.000000 18.000000 19.000000;
     0.000000 0.000000 0.000000 0.000000 0.000000 20.000000]*/

/* b= [
2.000000  2.000000  2.000000  2.000000  2.000000  2.000000;
2.000000  2.000000  2.000000  2.000000  2.000000  2.000000;
2.000000  2.000000  2.000000  2.000000  2.000000  2.000000;
2.000000  2.000000  2.000000  2.000000  2.000000  2.000000;
2.000000  2.000000  2.000000  2.000000  2.000000  2.000000;
2.000000  2.000000  2.000000  2.000000  2.000000  2.000000 ]*/

/*
b= [9.000000  10.000000  11.000000  12.000000  13.000000  14.000000;
15.000000  16.000000  17.000000  18.000000  19.000000  20.000000;
21.000000  22.000000  23.000000  24.000000  25.000000  26.000000;
27.000000  28.000000  29.000000  30.000000  31.000000  32.000000;
33.000000  34.000000  35.000000  36.000000  37.000000  38.000000;
39.000000  40.000000  41.000000  42.000000  43.000000  44.000000]
*/

/* out_ref = [34935.000000 53025.000000 71115.000000 89205.000000 107295.000000
125385.000000; 86260.000000 130937.000000 175584.000000 220231.000000
264878.000000 309525.000000; 115070.000000 174694.000000 234404.000000
294004.000000 353604.000000 413204.000000; 119244.000000 181071.000000
242990.000000 305014.000000 366828.000000 428642.000000; 99145.000000
150593.000000 202139.000000 253795.000000 305551.000000 357001.000000;
57620.000000 87565.000000 117614.000000 147778.000000 178046.000000
208391.000000]*/