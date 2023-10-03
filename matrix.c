#include <stdio.h>

// Define the dimensions of the matrices
#define ROW1 3
#define COL1 3
#define ROW2 3
#define COL2 3

// Function to perform matrix multiplication
void matrixMultiply(int mat1[][COL1], int mat2[][COL2], int result[][COL2])
{
    for (int i = 0; i < ROW1; i++)
    {
        for (int j = 0; j < COL2; j++)
        {
            result[i][j] = 0; // Initialize the result matrix element to zero
            for (int k = 0; k < COL1; k++)
            {
                result[i][j] += mat1[i][k] * mat2[k][j]; // Compute the matrix multiplication
            }
        }
    }
}

// Function to print a matrix
void printMatrix(int mat[][COL2])
{
    for (int i = 0; i < ROW1; i++)
    {
        for (int j = 0; j < COL2; j++)
        {
            printf("%d\t", mat[i][j]); // Print each element of the matrix
        }
        printf("\n"); // Move to the next row
    }
}

int main()
{
    int matrix1[ROW1][COL1] = {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}};

    int matrix2[ROW2][COL2] = {{9, 8, 7},
                               {6, 5, 4},
                               {3, 2, 1}};
    int result[ROW1][COL2];

    // Perform matrix multiplication
    matrixMultiply(matrix1, matrix2, result);

    // Print the matrices and the resulting matrix
    printf("Matrix 1:\n");
    printMatrix(matrix1);
    printf("\nMatrix 2:\n");
    printMatrix(matrix2);
    printf("\nResulting Matrix:\n");
    printMatrix(result);

    return 0;
}
