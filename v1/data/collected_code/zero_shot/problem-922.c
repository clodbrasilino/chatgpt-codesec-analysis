#include <stdio.h>

void findMaxProduct(int arr[], int n) {
    if (n < 2) {
        printf("No pair exists\n");
        return;
    }
  
    int max_product = arr[0] * arr[1];
    int max_i = 0, max_j = 1;
  
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] * arr[j] > max_product) {
                max_product = arr[i] * arr[j];
                max_i = i;
                max_j = j;
            }
        }
    }
  
    printf("Pair with highest product: (%d, %d)\n", arr[max_i], arr[max_j]);
}

int main() {
    int arr[] = {4, 6, 2, 9, 5, 10, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
  
    findMaxProduct(arr, n);
  
    return 0;
}