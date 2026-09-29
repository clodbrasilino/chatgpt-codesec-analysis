#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int is_product_even(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] == 0) {
            return 1;
        }
        if (array[i] % 2 == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int arr1[] = {1, 3, 5};
    int arr2[] = {1, 2, 5};
    int arr3[] = {0, 1, 3};
    int *arr4 = NULL;

    printf("%d\n", is_product_even(arr1, sizeof(arr1) / sizeof(arr1[0])));
    printf("%d\n", is_product_even(arr2, sizeof(arr2) / sizeof(arr2[0])));
    printf("%d\n", is_product_even(arr3, sizeof(arr3) / sizeof(arr3[0])));
    printf("%d\n", is_product_even(arr4, 0));

    return 0;
}