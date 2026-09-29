#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void findDifferences(int *arr, int size, int **result, int *resultSize) {
    *result = malloc((size - 1) * sizeof(int));
    if (*result == NULL) {
        *resultSize = 0;
        return;
    }
    for (int i = 0; i < size - 1; i++) {
        (*result)[i] = arr[i + 1] - arr[i];
    }
    *resultSize = size - 1;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *result = NULL;
    int resultSize;

    findDifferences(arr, size, &result, &resultSize);

    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}