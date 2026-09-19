#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  *  test case 2 failed: expected 36, got <no output>
  */

int find_kth_element(const int *arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 1 || k > size) {
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
    
    int result = temp[k - 1];
    free(temp);
    return result;
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    
    int result = find_kth_element(arr, size, k);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input parameters\n");
    }
    
    return 0;
}