#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int *find_common_index_elements(const int *arr1, size_t size1, const int *arr2, size_t size2, const int *arr3, size_t size3, size_t *out_size) {
    *out_size = 0;
    if (!arr1 || !arr2 || !arr3 || size1 == 0 || size2 == 0 || size3 == 0) {
        return NULL;
    }

    int *copy1 = NULL;
    int *copy2 = NULL;
    int *copy3 = NULL;
    int *result = NULL;

    copy1 = malloc(size1 * sizeof(int));
    if (!copy1) goto cleanup;

    copy2 = malloc(size2 * sizeof(int));
    if (!copy2) goto cleanup;

    copy3 = malloc(size3 * sizeof(int));
    if (!copy3) goto cleanup;

    size_t max_common = size1;
    if (size2 < max_common) max_common = size2;
    if (size3 < max_common) max_common = size3;

    result = malloc(max_common * sizeof(int));
    if (!result) goto cleanup;

    for (size_t idx = 0; idx < size1; idx++) {
        copy1[idx] = arr1[idx];
    }
    for (size_t idx = 0; idx < size2; idx++) {
        copy2[idx] = arr2[idx];
    }
    for (size_t idx = 0; idx < size3; idx++) {
        copy3[idx] = arr3[idx];
    }

    qsort(copy1, size1, sizeof(int), compare_ints);
    qsort(copy2, size2, sizeof(int), compare_ints);
    qsort(copy3, size3, sizeof(int), compare_ints);

    size_t i = 0, j = 0, k = 0, count = 0;
    while (i < size1 && j < size2 && k < size3) {
        if (copy1[i] == copy2[j] && copy2[j] == copy3[k]) {
            if (count == 0 || result[count - 1] != copy1[i]) {
                result[count++] = copy1[i];
            }
            i++;
            j++;
            k++;
        } else if (copy1[i] < copy2[j]) {
            i++;
        } else if (copy2[j] < copy3[k]) {
            j++;
        } else {
            k++;
        }
    }

    free(copy1);
    free(copy2);
    free(copy3);

    if (count == 0) {
        free(result);
        return NULL;
    }

    int *trimmed_result = realloc(result, count * sizeof(int));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    *out_size = count;
    return result;

cleanup:
    free(copy1);
    free(copy2);
    free(copy3);
    free(result);
    return NULL;
}

int main(void) {
    int arr1[] = {1, 5, 10, 20, 40, 80};
    int arr2[] = {6, 7, 20, 80, 100};
    int arr3[] = {3, 4, 15, 20, 30, 70, 80, 120};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    size_t out_size = 0;
    int *common = find_common_index_elements(arr1, size1, arr2, size2, arr3, size3, &out_size);

    if (common != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", common[i]);
        }
        printf("\n");
        free(common);
    } else {
        printf("No common elements found.\n");
    }

    return 0;
}