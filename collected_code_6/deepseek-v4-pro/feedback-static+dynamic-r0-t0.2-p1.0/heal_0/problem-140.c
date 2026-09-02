#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

int* extract_singly_occurring(Tuple *tuples, int tuple_count, int *result_size) {
    int *counts = NULL;
    int *result = NULL;
    int capacity = 0;
    int total_elements = 0;
    int i, j, k;
    int found;

    for (i = 0; i < tuple_count; i++) {
        total_elements += tuples[i].size;
    }

    counts = (int*)calloc(total_elements, sizeof(int));
    if (counts == NULL) {
        *result_size = 0;
        return NULL;
    }

    result = (int*)malloc(total_elements * sizeof(int));
    if (result == NULL) {
        free(counts);
        *result_size = 0;
        return NULL;
    }

    capacity = 0;
    for (i = 0; i < tuple_count; i++) {
        for (j = 0; j < tuples[i].size; j++) {
            found = 0;
            for (k = 0; k < capacity; k++) {
                if (result[k] == tuples[i].data[j]) {
                    counts[k]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                result[capacity] = tuples[i].data[j];
                counts[capacity] = 1;
                capacity++;
            }
        }
    }

    *result_size = 0;
    for (i = 0; i < capacity; i++) {
        if (counts[i] == 1) {
            result[*result_size] = result[i];
            (*result_size)++;
        }
    }

    free(counts);
    return result;
}

int main(void) {
    int tuple1_data[] = {1, 2, 3, 4};
    int tuple2_data[] = {3, 4, 5, 6};
    int tuple3_data[] = {7, 8, 9};
    Tuple tuples[3];
    int *result;
    int result_size;
    int i;

    tuples[0].data = tuple1_data;
    tuples[0].size = 4;
    tuples[1].data = tuple2_data;
    tuples[1].size = 4;
    tuples[2].data = tuple3_data;
    tuples[2].size = 3;

    result = extract_singly_occurring(tuples, 3, &result_size);

    for (i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}