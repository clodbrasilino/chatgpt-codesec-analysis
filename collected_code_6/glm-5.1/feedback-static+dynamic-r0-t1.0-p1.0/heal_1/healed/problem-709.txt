#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    int count;
} ValueCount;

int* count_unique_keys(Tuple* tuples, int num_tuples, int* result_size) {
    if (tuples == NULL || num_tuples <= 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    ValueCount* counts = malloc(num_tuples * sizeof(ValueCount));
    if (counts == NULL) {
        *result_size = 0;
        return NULL;
    }

    int unique_values = 0;

    for (int i = 0; i < num_tuples; i++) {
        int val_idx = -1;
        for (int j = 0; j < unique_values; j++) {
            if (counts[j].value == tuples[i].value) {
                val_idx = j;
                break;
            }
        }

        if (val_idx == -1) {
            val_idx = unique_values;
            counts[unique_values].value = tuples[i].value;
            counts[unique_values].count = 0;
            unique_values++;
        }

        int key_repeated_for_value = 0;
        for (int j = 0; j < i; j++) {
            if (tuples[j].value == tuples[i].value && tuples[j].key == tuples[i].key) {
                key_repeated_for_value = 1;
                break;
            }
        }

        if (!key_repeated_for_value) {
            counts[val_idx].count++;
        }
    }

    int* result = malloc(unique_values * 2 * sizeof(int));
    if (result == NULL) {
        free(counts);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < unique_values; i++) {
        result[i * 2] = counts[i].value;
        result[i * 2 + 1] = counts[i].count;
    }

    free(counts);
    *result_size = unique_values * 2;
    return result;
}

int main() {
    Tuple data[] = {{1, 10}, {2, 10}, {1, 10}, {3, 20}, {4, 20}, {4, 20}, {5, 30}};
    int num_tuples = sizeof(data) / sizeof(data[0]);
    int result_size = 0;

    int* result = count_unique_keys(data, num_tuples, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i += 2) {
            printf("Value: %d, Unique Keys: %d\n", result[i], result[i + 1]);
        }
        free(result);
    }

    return 0;
}