#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void find_min_indices(int *arr, int n, int **indices, int *count) {
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    *count = 0;
    *indices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (arr[i] == min) {
            (*indices)[(*count)++] = i;
        }
    }
}

int main() {
    int arr[] = {4, 2, 1, 3, 1, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *indices;
    int count;

    find_min_indices(arr, n, &indices, &count);

    printf("Indices of minimum values: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    free(indices);
    return 0;
}