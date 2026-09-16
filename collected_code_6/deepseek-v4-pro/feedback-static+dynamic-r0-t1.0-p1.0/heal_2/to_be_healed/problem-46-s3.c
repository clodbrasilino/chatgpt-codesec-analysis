#include <stdio.h>
#include <stdbool.h>

bool all_numbers_different(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return false;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {1, 2, 3, 2, 5};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {5};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {1, 1};
    /* Possible weaknesses found:
     *  Variable 'arr5' can be declared as const array [constVariable]
     */
    int arr5[] = {7, 8, 9, 10, 1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr6' can be declared as const array [constVariable]
     */
    int arr6[] = {4, 5, 6, 4, 7};

    printf("%d\n", all_numbers_different(arr1, 5));
    printf("%d\n", all_numbers_different(arr2, 5));
    printf("%d\n", all_numbers_different(arr3, 1));
    printf("%d\n", all_numbers_different(arr4, 2));
    printf("%d\n", all_numbers_different(arr5, 7));
    printf("%d\n", all_numbers_different(arr6, 5));
    printf("%d\n", all_numbers_different(NULL, 0));

    return 0;
}