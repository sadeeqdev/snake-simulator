#include <stdio.h>

int main()
{
  int firstMatrixRows, firstMatrixCols, secondMatrixRows, secondMatrixCols;

  // Prompt for the order of matrix 1
  printf("Enter the order of first matrix. e.g., 2,2 for a 2x2 matrix: ");
  scanf("%d,%d", &firstMatrixRows, &firstMatrixCols);

  // Prompt for the order of matrix 2
  printf("Enter the order of second matrxi. e.g., 2,2 for a 2x2 matrix: ");
  scanf("%d,%d", &secondMatrixRows, &secondMatrixCols);

  // Check if the matrices can be multiplied
  if (firstMatrixCols != secondMatrixRows)
  {
    printf("The matrices cannot be multiplied together\n");
    return 0;
  }

  int matrix1[firstMatrixRows][firstMatrixCols], matrix2[secondMatrixRows][secondMatrixCols], result[firstMatrixRows][secondMatrixCols];

  // Input elements for matrix 1
  printf("Enter elements of the first matrix:\n");
  for (int i = 0; i < firstMatrixRows; i++)
  {
    for (int j = 0; j < firstMatrixCols; j++)
    {
      scanf("%d", &matrix1[i][j]);
    }
  }

  // Input elements for matrix 2
  printf("Enter elements of the second matrix:\n");
  for (int i = 0; i < secondMatrixRows; i++)
  {
    for (int j = 0; j < secondMatrixCols; j++)
    {
      scanf("%d", &matrix2[i][j]);
    }
  }

  printf("The resulting matrix is:\n");

  // Multiply the matrices and print the result
  for (int i = 0; i < firstMatrixRows; i++)
  {
    for (int j = 0; j < secondMatrixCols; j++)
    {
      result[i][j] = 0;
      for (int k = 0; k < firstMatrixCols; k++)
      {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }

  return 0;
}
