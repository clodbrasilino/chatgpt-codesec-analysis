#include <stdio.h>
#include <stdlib.h>

void find_intersection(const int *array1, size_t size1, const int *array2, size_t size2, int **result, size_t *result_size) {
    if (!array1 || !array2 || !result || !result_size) {
        return;
    }

    size_t max_size = size1 < size2 ? size1 : size2;
    *result = (int *)malloc(max_size * sizeof(int));
    if (!*result) {
        *result_size = 0;
        return;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; ++i) {
        for (size_t j = 0; j < size2; ++j) {
            if (array1[i] == array2[j]) {
                int already_added = 0;
                for (size_t k = 0; k < count; ++k) {
                    if ((*result)[k] == array1[i]) {
                        already_added = 1;
                        break;
                    }
                }
                if (!already_added) {
                    (*result)[count++] = array1[i];
                }
                break;
            }
        }
    }

    *result_size = count;
    if (count > 0 && count < max_size) {
        int *temp = (int *)realloc(*result, count * sizeof(int));
        if (temp) {
            *result = temp;
        }
    } else if (count == 0) {
        free(*result);
        *result = NULL;
    }
}

int main(void) {
    int arr1[] = {1, 2, 4, 5, 6};
    int arr2[] = {2, 3, 5, 7};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    int *intersection = NULL;
    size_t intersect_size = 0;

    find_intersection(arr1, size1, arr2, size2, &intersection, &intersect_size);

    if (intersection) {
        for (size_t i = 0; i < intersect_size; i++) {
            printf("%d ", intersection[i]);
        }
        printf("\n");
        free(intersection);
    }

    return 0;
}