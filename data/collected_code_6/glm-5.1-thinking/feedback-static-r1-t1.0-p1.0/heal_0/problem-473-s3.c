#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *tuple_intersection(int **tuples, int *tuple_sizes, int num_tuples, int *result_size) {
    if (tuples == NULL || tuple_sizes == NULL || result_size == NULL || num_tuples <= 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    *result_size = 0;

    for (int i = 0; i < num_tuples; i++) {
        if (tuple_sizes[i] < 0) {
            return NULL;
        }
        if (tuple_sizes[i] > 0 && tuples[i] == NULL) {
            return NULL;
        }
    }

    if (tuple_sizes[0] <= 0) {
        return NULL;
    }

    size_t max_result = (size_t)tuple_sizes[0];
    int *result = (int *)malloc(max_result * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < tuple_sizes[0]; i++) {
        int candidate = tuples[0][i];
        int already_in_result = 0;
        for (int k = 0; k < *result_size; k++) {
            if (result[k] == candidate) {
                already_in_result = 1;
                break;
            }
        }
        if (already_in_result) {
            continue;
        }

        int in_all = 1;
        for (int j = 1; j < num_tuples; j++) {
            int found = 0;
            for (int k = 0; k < tuple_sizes[j]; k++) {
                if (tuples[j][k] == candidate) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                in_all = 0;
                break;
            }
        }

        if (in_all) {
            result[*result_size] = candidate;
            (*result_size)++;
        }
    }

    if (*result_size == 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void) {
    int t0[] = {1, 2, 3};
    int t1[] = {3, 2, 4};
    int t2[] = {5, 2, 3, 6};

    int *tuples[] = {t0, t1, t2};
    int tuple_sizes[] = {3, 3, 4};
    int num_tuples = 3;

    int result_size = 0;
    int *result = tuple_intersection(tuples, tuple_sizes, num_tuples, &result_size);

    if (result != NULL) {
        printf("Tuple intersection: {");
        for (int i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("}\n");
        free(result);
    } else {
        printf("No intersection found.\n");
    }

    return 0;
}