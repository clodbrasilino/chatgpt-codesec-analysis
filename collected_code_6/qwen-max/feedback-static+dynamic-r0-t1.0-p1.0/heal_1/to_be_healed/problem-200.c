#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void find_max_indices(int *arr, int n, int **indices, int *count) {
    if (n <= 0) return;
    int max_val = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    *count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == max_val) {
            (*count)++;
        }
    }
    *indices = (int *)malloc(*count * sizeof(int));
    if (*indices == NULL) return;
    *count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == max_val) {
            (*indices)[*count] = i;
            (*count)++;
        }
    }
}

int main() {
    int arr[] = {1, 3, 2, 3, 5, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *indices = NULL;
    int count = 0;

    find_max_indices(arr, n, &indices, &count);

    for (int i = 0; i < count; ++i) {
        printf("%d ", indices[i]);
    }
    free(indices);
    return 0;
}