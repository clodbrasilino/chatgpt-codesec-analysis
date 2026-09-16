#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void find_min_indices(int *arr, int n, int **result, int *result_count) {
    if (n == 0) return;
    *result = NULL;
    *result_count = 0;

    int min_val = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == min_val) {
            count++;
        }
    }

    *result = (int*)malloc(count * sizeof(int));
    if (*result == NULL) {
        *result_count = 0;
        return;
    }

    *result_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == min_val) {
            (*result)[*result_count] = i;
            (*result_count)++;
        }
    }
}

int main() {
    int arr[] = {4, 2, 5, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *result = NULL;
    int result_count = 0;

    find_min_indices(arr, n, &result, &result_count);

    printf("Indices of minimum values: ");
    for (int i = 0; i < result_count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}