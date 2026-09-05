#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains_duplicate(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                return true;
            }
        }
    }
    return false;
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
     *  Variable 'arr3' can be declared as pointer to const [constVariablePointer]
     */
    int *arr3 = NULL;

    bool res1 = contains_duplicate(arr1, 5);
    bool res2 = contains_duplicate(arr2, 5);
    bool res3 = contains_duplicate(arr3, 5);

    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);

    return 0;
}