#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int list_to_int(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    int result = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            int abs_val = -list[i];

            if (result != 0 && INT_MIN / result > -10) {
                return result;
            }
            if (result < INT_MIN / 10) {
                return INT_MIN;
            }
            result *= 10;
            if (INT_MIN - result > -abs_val) {
                return INT_MIN;
            }
            result -= abs_val;
        } else {
            int val = list[i];

            if (result != 0 && INT_MAX / result < 10) {
                return result;
            }
            if (result > INT_MAX / 10) {
                return INT_MAX;
            }
            result *= 10;
            if (val > INT_MAX - result) {
                return INT_MAX;
            }
            result += val;
        }
    }

    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {9, 8, 7, 6};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {};
    int arr4[] = {-4, 2};
    int arr5[] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = 0;
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    size_t size5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("%d\n", list_to_int(arr1, size1));
    printf("%d\n", list_to_int(arr2, size2));
    printf("%d\n", list_to_int(NULL, size3));
    printf("%d\n", list_to_int(arr3, size3));
    printf("%d\n", list_to_int(arr4, size4));
    printf("%d\n", list_to_int(arr5, size5));

    return 0;
}