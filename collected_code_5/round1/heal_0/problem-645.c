#include <stdio.h>

long long find_product(int rows, int cols, int k, int array[rows][cols]) {
  if (k >= cols || k < 0)
    return -1; 
  
  long long product = 1;
  for (int i = 0; i < rows; i++) {
    product *= array[i][k];
  }
  
  return product;
}

int main() {
  int rows = 3;
  int cols = 4;
  int k = 2;
  int array[rows][cols];
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      array[i][j] = j + 1;
    }
  }
  
  long long product = find_product(rows, cols, k, array);
  
  if(product != -1){
    printf("The product of values at index %d in the tuples is %lld.\n", k, product);
  }else{
    printf("Index out of bound.\n");
  }
  
  return 0;
}