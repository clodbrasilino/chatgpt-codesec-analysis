#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ARRAY_SIZE 10
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  *  test case 1 failed: expected -1, got <no output>
  */

int find_first_duplicate(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int min_val = arr[0];
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    if (max_val - min_val < 0) {
        return -1;
    }

    long long range = (long long)max_val - min_val + 1;
    if (range <= 0 || range > (long long)INT_MAX) {
        return -1;
    }

    int *count = (int *)calloc((size_t)range, sizeof(int));
    if (count == NULL) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        long long index = (long long)arr[i] - min_val;
        if (index < 0 || index >= range) {
            continue;
        }
        count[index]++;
        if (count[index] == 2) {
            free(count);
            return arr[i];
        }
    }

    free(count);
    return -1;
}

int main(void) {
    const int arr[ARRAY_SIZE] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int result = find_first_duplicate(arr, ARRAY_SIZE);

    printf("%d\n", result);

    return 0;
}