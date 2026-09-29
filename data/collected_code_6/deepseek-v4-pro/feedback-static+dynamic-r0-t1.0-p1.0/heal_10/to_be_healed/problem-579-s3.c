#include <stdio.h>
#include <stdlib.h>

int is_present(const int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected [3, 6, 7, 10], got <no output>
  *  test case 2 failed: expected [34, 36, 11, 25], got <no output>
  *  test case 1 failed: expected [1, 4, 7, 9], got <no output>
  */

int* find_dissimilar(const int *tuple1, int size1, const int *tuple2, int size2, int *result_size) {
    int *result = (int*)malloc((size1 + size2) * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < size1; i++) {
        if (!is_present(tuple2, size2, tuple1[i])) {
            result[count++] = tuple1[i];
        }
    }

    for (int i = 0; i < size2; i++) {
        if (!is_present(tuple1, size1, tuple2[i])) {
            result[count++] = tuple2[i];
        }
    }

    *result_size = count;

    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int *final_result = (int*)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    return final_result;
}

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int result_size = 0;

    int *dissimilar = find_dissimilar(tuple1, size1, tuple2, size2, &result_size);

    if (result_size == 0) {
        printf("[]\n");
        free(dissimilar);
        return 0;
    }

    if (dissimilar == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    qsort(dissimilar, result_size, sizeof(int), compare_ints);

    printf("[");
    for (int i = 0; i < result_size; i++) {
        printf("%d", dissimilar[i]);
        if (i < result_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(dissimilar);
    return 0;
}