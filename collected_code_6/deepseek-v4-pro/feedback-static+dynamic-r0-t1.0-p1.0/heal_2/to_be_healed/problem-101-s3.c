#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 8, got 24
  *  test case 2 failed: expected 36, got 25
  */

int find_kth_element(const int *arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size) {
        return -1;
    }
    
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    
    for (int i = 0; i < k + 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (temp[j] < temp[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int swap = temp[i];
            temp[i] = temp[min_idx];
            temp[min_idx] = swap;
        }
    }
    
    int result = temp[k];
    free(temp);
    return result;
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    int result = find_kth_element(arr, size, k);
    if (result != -1) {
        printf("The %dth element is: %d\n", k, result);
    } else {
        printf("Invalid input parameters\n");
    }
    
    return 0;
}