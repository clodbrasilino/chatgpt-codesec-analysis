#include <stdio.h>
#include <stdlib.h>

int records_with_similar_occurrences(const int *records, size_t n, int **similar_records, size_t *similar_count) {
    if (similar_records == NULL || similar_count == NULL) return -1;
    if (n > 0 && records == NULL) return -1;

    *similar_records = NULL;
    *similar_count = 0;

    if (n == 0) return 0;

    int *values = malloc(n * sizeof(int));
    size_t *counts = calloc(n, sizeof(size_t));
    if (values == NULL || counts == NULL) {
        free(values);
        free(counts);
        return -1;
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < n; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (values[j] == records[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            values[unique_count] = records[i];
            counts[unique_count] = 1;
            unique_count++;
        }
    }

    int *result = malloc(unique_count * sizeof(int));
    if (result == NULL) {
        free(values);
        free(counts);
        return -1;
    }

    int *added = calloc(unique_count, sizeof(int));
    if (added == NULL) {
        free(values);
        free(counts);
        free(result);
        return -1;
    }

    size_t output_count = 0;
    for (size_t i = 0; i < unique_count; i++) {
        if (added[i]) continue;

        size_t freq = counts[i];
        size_t group_start = output_count;
        size_t group_size = 0;

        for (size_t j = 0; j < unique_count; j++) {
            if (!added[j] && counts[j] == freq) {
                result[output_count++] = values[j];
                added[j] = 1;
                group_size++;
            }
        }

        if (group_size <= 1) {
            output_count = group_start;
        }
    }

    free(values);
    free(counts);
    free(added);

    if (output_count == 0) {
        free(result);
        *similar_records = NULL;
        *similar_count = 0;
        return 0;
    }

    int *shrunk = realloc(result, output_count * sizeof(int));
    if (shrunk == NULL) {
        free(result);
        return -1;
    }

    *similar_records = shrunk;
    *similar_count = output_count;
    return 0;
}

int main(void) {
    int records[] = {1, 2, 2, 3, 3, 3, 4};
    size_t n = sizeof(records) / sizeof(records[0]);
    int *similar = NULL;
    size_t similar_count = 0;

    int ret = records_with_similar_occurrences(records, n, &similar, &similar_count);
    if (ret != 0) {
        printf("Error\n");
        return 1;
    }

    printf("Records with similar occurrences:");
    for (size_t i = 0; i < similar_count; i++) {
        printf(" %d", similar[i]);
    }
    printf("\n");

    free(similar);
    return 0;
}