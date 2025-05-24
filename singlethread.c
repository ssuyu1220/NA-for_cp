#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 800
#define K 800
#define N 800

// matrix_a(M*K)*matrix_a(K*N)=matrix_c(M*N)
int matrix_a[M][K];
int matrix_b[K][N];
int matrix_c[M][N];

// calaulate matrix_a*matrix_b=matrix_c
void matrix_multiply() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; ++j) {
            int sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_c[i][j] = sum;
        }
    }
}

int main() {
    // implement data of matrix_a
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            matrix_a[i][j] = i + j;
        }
    }
    // implement data of matrix_b
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            matrix_b[i][j] = abs(i - j);
        }
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // start timer

    matrix_multiply();

    // open file
    FILE *file = fopen("singlethread_matrix_c.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }
    // write result to singlethread_matrix_c.txt
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            fprintf(file, "%d ", matrix_c[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("matrix_c has been written to singlethread_matrix_c.txt\n");

    clock_gettime(CLOCK_MONOTONIC, &end); // end timer
    double dur =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("total time of matrix multiplication (single thread): %lf secs\n",
           dur);

    return 0;
}
