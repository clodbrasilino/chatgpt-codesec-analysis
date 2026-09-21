#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
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

    int* odd_arr = (int*)malloc((count > 0 ? count : 1) * sizeof(int));
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
            if (size < 10000) {
                arr[size++] = (int)strtol(argv[i], NULL, 10);
            }
        }
    } else {
        int val;
        while (1) {
            int res = scanf("%d", &val);
            if (res == 1) {
                if (size < 10000) {
                    arr[size++] = val;
                }
            } else if (res == EOF) {
                break;
            } else {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                getchar();
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