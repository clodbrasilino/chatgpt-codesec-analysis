#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int* find_differences(int* arr, size_t size) {
    if (arr == NULL || size < 2) {
        return NULL;
    }

    int* differences = (int*)malloc((size - 1) * sizeof(int));
    if (differences == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        differences[i] = arr[i + 1] - arr[i];
    }

    return differences;
}

int main() {
    int arr[] = {10, 15, 23, 34, 40};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(arr)/sizeof(arr[0])', assigned value is 5
     */
    size_t size = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  Condition 'size<2' is always false
     *  Condition 'size<2' is always false [knownConditionTrueFalse]
     */
    if (size < 2) {
        return EXIT_FAILURE;
    }

    int* diffs = find_differences(arr, size);
    if (diffs == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        printf("%d ", diffs[i]);
    }
    printf("\n");

    free(diffs);

    return EXIT_SUCCESS;
}