#include <stdio.h>

int countSubsequenceProduct(int array[], int array_size, int k) {
  int dp_matrix[array_size + 1][k + 1];
  for (int i = 0; i <= array_size; ++i) {
    for (int j = 0; j <= k; ++j) {
      if (i == 0) {
        dp_matrix[i][j] = 0;
      } else if (j == 0) {
        dp_matrix[i][j] = 1;
      }
    }
  }
  for (int i = 1; i <= array_size; ++i) {
    for (int j = 1; j <= k; ++j) {
      if (array[i - 1] > j) {
        dp_matrix[i][j] = dp_matrix[i - 1][j];
      } else {
        dp_matrix[i][j] = dp_matrix[i - 1][j] + dp_matrix[i - 1][j/array[i - 1]];
      }
    }
  }
  return dp_matrix[array_size][k];
}

int main() {
  int array[] = {1, 2, 3, 4};
  int k = 10;
  int array_size = sizeof(array)/sizeof(array[0]);
  printf("%d\n", countSubsequenceProduct(array, array_size, k));
  return 0;
}