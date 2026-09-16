#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    double value;
} TupleRecord;

int extract_index_of_min(const TupleRecord *tuples, size_t count, int *out_index) {
    size_t min_pos;
    size_t i;

    if (tuples == NULL || count == 0 || out_index == NULL) {
        return -1;
    }

    min_pos = 0;
    for (i = 1; i < count; i++) {
        if (tuples[i].value < tuples[min_pos].value) {
            min_pos = i;
        }
    }

    *out_index = tuples[min_pos].index;
    return 0;
}

int main(void) {
    TupleRecord records[] = {
        {10, 3.14},
        {20, 1.41},
        {30, 2.71},
        {40, 0.58},
        {50, 5.00}
    };
    size_t record_count = sizeof(records) / sizeof(records[0]);
    int min_index = 0;
    int result;

    result = extract_index_of_min(records, record_count, &min_index);
    if (result != 0) {
        fprintf(stderr, "Error extracting minimum value index.\n");
        return EXIT_FAILURE;
    }

    printf("Index of minimum value record: %d\n", min_index);
    return EXIT_SUCCESS;
}