#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int* remove_negatives(int *arr, int n, int *new_size) {
    int *result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0) {
            result[count++] = arr[i];
        }
    }
    *new_size = count;
    /* Possible weaknesses found:
     *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
     */
    result = (int*)realloc(result, count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    return result;
}

int main() {
    int arr[] = {-1, 2, -3, 4, 5, -6, 7, 8, -9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int new_size;
    int *filtered_arr = remove_negatives(arr, n, &new_size);
    if (filtered_arr != NULL) {
        for (int i = 0; i < new_size; ++i) {
            printf("%d ", filtered_arr[i]);
        }
        free(filtered_arr);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}