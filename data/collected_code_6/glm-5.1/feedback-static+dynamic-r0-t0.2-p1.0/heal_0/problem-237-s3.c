#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int count;
} Record;

int check_similar_occurrences(int *tuples, int tuple_count, int tuple_size) {
    if (tuples == NULL || tuple_count <= 0 || tuple_size <= 0) {
        return 0;
    }

    int total_elements = tuple_count * tuple_size;
    Record *records = (Record *)malloc(total_elements * sizeof(Record));
    if (records == NULL) {
        return 0;
    }

    int unique_count = 0;

    for (int i = 0; i < total_elements; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (records[j].key == tuples[i]) {
                records[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            records[unique_count].key = tuples[i];
            records[unique_count].count = 1;
            unique_count++;
        }
    }

    int *frequency_counts = (int *)calloc(unique_count + 1, sizeof(int));
    if (frequency_counts == NULL) {
        free(records);
        return 0;
    }

    for (int i = 0; i < unique_count; i++) {
        frequency_counts[records[i].count]++;
    }

    int similar_occurrences = 0;
    for (int i = 1; i <= unique_count; i++) {
        if (frequency_counts[i] > 1) {
            similar_occurrences += frequency_counts[i];
        }
    }

    free(records);
    free(frequency_counts);

    return similar_occurrences;
}

int main() {
    int tuples[][3] = {
        {1, 2, 3},
        {4, 2, 5},
        {1, 6, 7},
        {8, 9, 3}
    };

    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int tuple_size = sizeof(tuples[0]) / sizeof(tuples[0][0]);

    int result = check_similar_occurrences((int *)tuples, tuple_count, tuple_size);

    printf("%d\n", result);

    return 0;
}