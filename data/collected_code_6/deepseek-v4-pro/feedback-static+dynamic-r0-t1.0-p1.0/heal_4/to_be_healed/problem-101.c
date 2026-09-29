#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  *  test case 2 failed: expected 36, got <no output>
  */

int find_kth_element(const int *arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size) {
        fprintf(stderr, "Invalid input parameters\n");
        exit(EXIT_FAILURE);
    }
    return arr[k];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    int result = find_kth_element(arr, size, k);
    printf("The %dth element is: %d\n", k, result);
    
    return 0;
}