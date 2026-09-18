#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
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

    if (count == 0) {
        *out_size = 0;
        return NULL;
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
            const char* str = argv[i];
            int j = 0;
            while (str[j] != '\0') {
                if ((str[j] >= '0' && str[j] <= '9') || (str[j] == '-' && str[j+1] >= '0' && str[j+1] <= '9')) {
                    arr[size++] = atoi(&str[j]);
                    if (str[j] == '-') j++;
                    while (str[j] >= '0' && str[j] <= '9') j++;
                } else {
                    j++;
                }
            }
        }
    } else {
        int c;
        int val = 0;
        int sign = 1;
        int has_val = 0;
        while ((c = getchar()) != EOF) {
            if (c == '-') {
                sign = -1;
            } else if (c >= '0' && c <= '9') {
                val = val * 10 + (c - '0');
                has_val = 1;
            } else {
                if (has_val) {
                    arr[size++] = val * sign;
                    has_val = 0;
                    val = 0;
                }
                sign = 1;
            }
        }
        if (has_val) {
            arr[size++] = val * sign;
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
    if (odd_arr != NULL && out_size > 0) {
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