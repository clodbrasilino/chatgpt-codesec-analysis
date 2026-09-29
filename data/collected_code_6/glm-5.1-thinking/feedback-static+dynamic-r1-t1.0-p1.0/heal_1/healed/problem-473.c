#include <stdio.h>
#include <stdlib.h>

int* tuple_intersection(int** tuples, const int* sizes, int num_tuples, int* result_size) {
    if (tuples == NULL || sizes == NULL || result_size == NULL || num_tuples <= 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (tuples[0] == NULL || sizes[0] <= 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc((size_t)sizes[0] * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int res_idx = 0;

    for (int i = 0; i < sizes[0]; i++) {
        int elem = tuples[0][i];
        int is_dup = 0;
        for (int k = 0; k < res_idx; k++) {
            if (result[k] == elem) {
                is_dup = 1;
                break;
            }
        }
        if (is_dup) {
            continue;
        }

        int found_in_all = 1;
        for (int j = 1; j < num_tuples; j++) {
            if (tuples[j] == NULL || sizes[j] <= 0) {
                found_in_all = 0;
                break;
            }
            int found = 0;
            for (int l = 0; l < sizes[j]; l++) {
                if (tuples[j][l] == elem) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                found_in_all = 0;
                break;
            }
        }

        if (found_in_all) {
            result[res_idx++] = elem;
        }
    }

    *result_size = res_idx;
    if (res_idx == 0) {
        free(result);
        return NULL;
    }

    int* temp = realloc(result, (size_t)res_idx * sizeof(int));
    if (temp != NULL) {
        result = temp;
    }

    return result;
}

int main() {
    int t1[] = {1, 2, 3};
    int t2[] = {3, 2, 5};
    int t3[] = {2, 3, 6};

    int* tuples[] = {t1, t2, t3};
    const int sizes[] = {3, 3, 3};
    int num_tuples = 3;
    int result_size = 0;

    int* result = tuple_intersection(tuples, sizes, num_tuples, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}