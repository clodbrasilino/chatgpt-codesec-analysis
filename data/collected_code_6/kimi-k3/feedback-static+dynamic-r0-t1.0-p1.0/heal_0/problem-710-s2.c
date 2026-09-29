#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} TupleRecord;

int tuple_record_init(TupleRecord *record, const int *values, size_t count) {
    if (record == NULL || (values == NULL && count > 0)) {
        return -1;
    }

    record->data = NULL;
    record->size = 0;

    if (count == 0) {
        return 0;
    }

    int *buffer = (int *)malloc(count * sizeof(*buffer));
    if (buffer == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        buffer[i] = values[i];
    }

    record->data = buffer;
    record->size = count;
    return 0;
}

int tuple_record_first(const TupleRecord *record, int *out_value) {
    if (record == NULL || out_value == NULL || record->data == NULL || record->size == 0) {
        return -1;
    }

    *out_value = record->data[0];
    return 0;
}

int tuple_record_last(const TupleRecord *record, int *out_value) {
    if (record == NULL || out_value == NULL || record->data == NULL || record->size == 0) {
        return -1;
    }

    *out_value = record->data[record->size - 1];
    return 0;
}

void tuple_record_destroy(TupleRecord *record) {
    if (record == NULL) {
        return;
    }

    free(record->data);
    record->data = NULL;
    record->size = 0;
}

int main(void) {
    const int values[] = {10, 20, 30, 40, 50};
    TupleRecord record;
    int first = 0;
    int last = 0;

    if (tuple_record_init(&record, values, sizeof(values) / sizeof(values[0])) != 0) {
        fprintf(stderr, "Failed to initialize tuple record\n");
        return EXIT_FAILURE;
    }

    if (tuple_record_first(&record, &first) != 0) {
        fprintf(stderr, "Failed to access first element\n");
        tuple_record_destroy(&record);
        return EXIT_FAILURE;
    }

    if (tuple_record_last(&record, &last) != 0) {
        fprintf(stderr, "Failed to access last element\n");
        tuple_record_destroy(&record);
        return EXIT_FAILURE;
    }

    printf("First: %d\n", first);
    printf("Last: %d\n", last);

    tuple_record_destroy(&record);
    return EXIT_SUCCESS;
}