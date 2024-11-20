#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX 3  // Size of the matrix (change this for larger matrices)

int matrixA[MAX][MAX], matrixB[MAX][MAX], result[MAX][MAX];

// Struct to hold the row and column information for each thread
typedef struct {
    int row;
    int col;
} thread_data;

// Function to perform matrix multiplication
void *multiply(void *arg) {
    thread_data *data = (thread_data *)arg;
    int row = data->row;
    int col = data->col;
    
    result[row][col] = 0;
    for (int k = 0; k < MAX; k++) {
        result[row][col] += matrixA[row][k] * matrixB[k][col];
    }
    
    pthread_exit(NULL);
}

// Function to print a matrix
void printMatrix(int matrix[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    pthread_t threads[MAX][MAX];
    thread_data threadArgs[MAX][MAX];

    // Initialize matrices A and B
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            scanf("%d", &matrixB[i][j]);
        }
    }

    // Create threads to compute each element of the result matrix
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            threadArgs[i][j].row = i;
            threadArgs[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, (void *)&threadArgs[i][j]);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the result matrix
    printf("Resultant Matrix:\n");
    printMatrix(result);

    return 0;
}
