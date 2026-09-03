#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int max_sublist_length(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int max_length = 1;
    int current_length = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 1;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    int arr1[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", max_sublist_length(arr1, size1));

    int arr2[] = {5, 5, 5, 5, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", max_sublist_length(arr2, size2));

    int arr3[] = {1, 2, 3, 4, 5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", max_sublist_length(arr3, size3));

    int arr4[] = {7};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", max_sublist_length(arr4, size4));

    printf("%d\n", max_sublist_length(NULL, 0));

    return 0;
}