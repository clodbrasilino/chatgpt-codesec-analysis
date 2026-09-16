#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int *find_common_elements(const int *arr1, size_t size1,
                          const int *arr2, size_t size2,
                          const int *arr3, size_t size3,
                          size_t *out_size) {
    *out_size = 0;
    if (size1 == 0 || size2 == 0 || size3 == 0) {
        return NULL;
    }

    int *sorted1 = malloc(size1 * sizeof(int));
    int *sorted2 = malloc(size2 * sizeof(int));
    int *sorted3 = malloc(size3 * sizeof(int));

    if (!sorted1 || !sorted2 || !sorted3) {
        free(sorted1);
        free(sorted2);
        free(sorted3);
        return NULL;
    }

    memcpy(sorted1, arr1, size1 * sizeof(int));
    memcpy(sorted2, arr2, size2 * sizeof(int));
    memcpy(sorted3, arr3, size3 * sizeof(int));

    qsort(sorted1, size1, sizeof(int), compare_ints);
    qsort(sorted2, size2, sizeof(int), compare_ints);
    qsort(sorted3, size3, sizeof(int), compare_ints);

    size_t max_size = size1;
    if (size2 < max_size) max_size = size2;
    if (size3 < max_size) max_size = size3;

    int *result = malloc(max_size * sizeof(int));
    if (!result) {
        free(sorted1);
        free(sorted2);
        free(sorted3);
        return NULL;
    }

    size_t i = 0, j = 0, k = 0;
    size_t count = 0;

    while (i < size1 && j < size2 && k < size3) {
        if (sorted1[i] == sorted2[j] && sorted2[j] == sorted3[k]) {
            if (count == 0 || result[count - 1] != sorted1[i]) {
                result[count++] = sorted1[i];
            }
            i++;
            j++;
            k++;
        } else if (sorted1[i] < sorted2[j]) {
            i++;
        } else if (sorted2[j] < sorted3[k]) {
            j++;
        } else {
            k++;
        }
    }

    free(sorted1);
    free(sorted2);
    free(sorted3);

    if (count == 0) {
        free(result);
        return NULL;
    }

    *out_size = count;
    int *final_result = realloc(result, count * sizeof(int));
    if (final_result) {
        return final_result;
    }

    return result;
}

int main(void) {
    int arr1[] = {1, 5, 10, 20, 40, 80};
    int arr2[] = {6, 7, 20, 80, 100};
    int arr3[] = {3, 4, 15, 20, 30, 70, 80, 120};

    size_t out_size = 0;
    int *common = find_common_elements(arr1, sizeof(arr1) / sizeof(arr1[0]),
                                       arr2, sizeof(arr2) / sizeof(arr2[0]),
                                       arr3, sizeof(arr3) / sizeof(arr3[0]),
                                       &out_size);

    if (common) {
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