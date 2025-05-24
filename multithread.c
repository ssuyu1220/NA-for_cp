#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 800
#define K 800
#define N 800
#define NUM_THREADS 4

// matrix_a(M*K)*matrix_a(K*N)=matrix_c(M*N)
int matrix_a[M][K];
int matrix_b[K][N];
int matrix_c[M][N];

typedef struct {
    int start_row;
    int end_row;
    int id; // thread id
} ThreadArg;

// calaulate matrix_a*matrix_b=matrix_c
void *matrix_multiply(void *arg) {
    ThreadArg *t_arg = (ThreadArg *)arg;

    for (int i = t_arg->start_row; i < t_arg->end_row; i++) {
        for (int j = 0; j < N; ++j) {
            int sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_c[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}

int main() {
    // implement data of matrix_a
    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            matrix_a[i][j] = i + j;

    // implement data of matrix_b
    for (int i = 0; i < K; i++)
        for (int j = 0; j < N; j++)
            matrix_b[i][j] = abs(i - j);

    pthread_t threads[NUM_THREADS];
    ThreadArg args[NUM_THREADS];

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int rows_num = M / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start_row = i * rows_num;
        args[i].end_row = (i + 1) * rows_num;
        pthread_create(&threads[i], NULL, matrix_multiply, &args[i]);
    }

    // Wait all of the threads complete
    for (int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);

    // write result to matrix_c.txt
    FILE *file = fopen("matrix_c.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            fprintf(file, "%d ", matrix_c[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("matrix_c has been written to matrix_c.txt\n");
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double dur =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Multiplication done. Total time: %lf seconds\n", dur);

    return 0;
}
