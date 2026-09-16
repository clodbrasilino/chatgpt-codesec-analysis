#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int sequential_search(int *array, size_t size, int target) {
    if (array == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (array[i] == target) {
            return (int)i;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    int arr[] = {4, 2, 7, 1, 9, 5, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int index = sequential_search(arr, size, target);

    if (index != -1) {
        printf("Element %d found at index %d\n", target, index);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    return EXIT_SUCCESS;
}