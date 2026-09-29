#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 36, got 25
  *  test case 1 failed: expected 8, got 24
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
    
    qsort(temp, size, sizeof(int), compare);
    
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
        printf("%d\n", result);
    } else {
        printf("Invalid input parameters\n");
    }
    
    return 0;
}