#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

int count_even(const int *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int even_count = count_even(arr, size);
    printf("Number of even elements: %d\n", even_count);
    return 0;
}