#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  */

int* filter_odd_numbers(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    int* odd_arr = (int*)malloc(count * sizeof(int));
    if (odd_arr == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            odd_arr[index++] = arr[i];
        }
    }

    *out_size = count;
    return odd_arr;
}

int main(int argc, const char *argv[]) {
    int arr[10000];
    size_t size = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            arr[size++] = atoi(argv[i]);
        }
    } else {
        int val;
        while (scanf("%d", &val) == 1) {
            arr[size++] = val;
        }
        if (size == 0) {
            const int default_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            for (int i = 0; i < 10; i++) {
                arr[size++] = default_arr[i];
            }
        }
    }

    size_t out_size = 0;
    int* odd_arr = filter_odd_numbers(arr, size, &out_size);

    printf("[");
    if (odd_arr != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d", odd_arr[i]);
            if (i < out_size - 1) {
                printf(", ");
            }
        }
        free(odd_arr);
    }
    printf("]\n");

    return EXIT_SUCCESS;
}