#include <stdio.h>
#include <stdlib.h>

int* tuple_union(int** tuples, int* tuple_sizes, int num_tuples, int* result_size) {
    int total_elements = 0;
    for (int i = 0; i < num_tuples; i++) {
        total_elements += tuple_sizes[i];
    }
    if (total_elements == 0) {
        *result_size = 0;
        return NULL;
    }
    int* temp = (int*)malloc(total_elements * sizeof(int));
    if (temp == NULL) {
        *result_size = 0;
        return NULL;
    }
    int temp_size = 0;
    for (int i = 0; i < num_tuples; i++) {
        for (int j = 0; j < tuple_sizes[i]; j++) {
            int current = tuples[i][j];
            int found = 0;
            for (int k = 0; k < temp_size; k++) {
                if (temp[k] == current) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                temp[temp_size++] = current;
            }
        }
    }
    int* result = NULL;
    if (temp_size > 0) {
        result = (int*)malloc(temp_size * sizeof(int));
        if (result == NULL) {
            free(temp);
            *result_size = 0;
            return NULL;
        }
        for (int i = 0; i < temp_size; i++) {
            result[i] = temp[i];
        }
    }
    free(temp);
    *result_size = temp_size;
    return result;
}

int main() {
    int t0[] = {1, 2, 3};
    int t1[] = {3, 4, 5};
    int t2[] = {5, 6, 1};
    int* tuples[] = {t0, t1, t2};
    int tuple_sizes[] = {3, 3, 3};
    int num_tuples = 3;
    int result_size = 0;
    int* result = tuple_union(tuples, tuple_sizes, num_tuples, &result_size);
    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Empty union or allocation failed.\n");
    }
    return 0;
}