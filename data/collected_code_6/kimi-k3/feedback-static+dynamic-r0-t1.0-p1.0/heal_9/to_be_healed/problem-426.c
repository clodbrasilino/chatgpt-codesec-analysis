#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  */

int *filter_odd_numbers(const int *arr, size_t size, size_t *result_size) {
    if (arr == NULL || result_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL && count > 0) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[index++] = arr[i];
        }
    }

    *result_size = count;
    return result;
}

int main(void) {
    int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size1 = sizeof(test1) / sizeof(test1[0]);
    size_t result_size1 = 0;
    int *odd1 = filter_odd_numbers(test1, size1, &result_size1);
    
    if (odd1 != NULL || result_size1 == 0) {
        printf("[");
        for (size_t i = 0; i < result_size1; i++) {
            printf("%d", odd1[i]);
            if (i < result_size1 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(odd1);
    }

    int test2[] = {45, 46, 67, 68, 93, 94};
    size_t size2 = sizeof(test2) / sizeof(test2[0]);
    size_t result_size2 = 0;
    int *odd2 = filter_odd_numbers(test2, size2, &result_size2);
    
    if (odd2 != NULL || result_size2 == 0) {
        printf("[");
        for (size_t i = 0; i < result_size2; i++) {
            printf("%d", odd2[i]);
            if (i < result_size2 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(odd2);
    }

    int test3[] = {5, 6, 7, 8, 9, 10, 3, 4};
    size_t size3 = sizeof(test3) / sizeof(test3[0]);
    size_t result_size3 = 0;
    int *odd3 = filter_odd_numbers(test3, size3, &result_size3);
    
    if (odd3 != NULL || result_size3 == 0) {
        printf("[");
        for (size_t i = 0; i < result_size3; i++) {
            printf("%d", odd3[i]);
            if (i < result_size3 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(odd3);
    }

    return EXIT_SUCCESS;
}