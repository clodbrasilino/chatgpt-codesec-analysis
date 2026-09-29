#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_RECORD
} ValueType;

typedef struct Record Record;

typedef struct {
    ValueType type;
    union {
        int integer;
        Record *record;
    } data;
} Value;

struct Record {
    size_t count;
    Value *values;
};

static void record_destroy(Record *record)
{
    size_t i;

    if (record == NULL) {
        return;
    }

    for (i = 0; i < record->count; ++i) {
        if (record->values[i].type == VALUE_RECORD) {
            record_destroy(record->values[i].data.record);
        }
    }

    free(record->values);
    free(record);
}

static int record_remove_nested(Record *tuple, size_t index)
{
    size_t i;

    if (tuple == NULL || index >= tuple->count ||
        tuple->values[index].type != VALUE_RECORD) {
        return -1;
    }

    record_destroy(tuple->values[index].data.record);

    for (i = index; i + 1U < tuple->count; ++i) {
        tuple->values[i] = tuple->values[i + 1U];
    }

    --tuple->count;

    if (tuple->count == 0U) {
        free(tuple->values);
        tuple->values = NULL;
    }

    return 0;
}

static Record *record_create(size_t count)
{
    Record *record = calloc(1U, sizeof(*record));

    if (record == NULL) {
        return NULL;
    }

    if (count > 0U) {
        if (count > SIZE_MAX / sizeof(*record->values)) {
            free(record);
            return NULL;
        }

        record->values = calloc(count, sizeof(*record->values));
        if (record->values == NULL) {
            free(record);
            return NULL;
        }
    }

    record->count = count;
    return record;
}

int main(void)
{
    Record *tuple = record_create(3U);
    Record *nested = record_create(2U);

    if (tuple == NULL || nested == NULL) {
        record_destroy(tuple);
        record_destroy(nested);
        return EXIT_FAILURE;
    }

    nested->values[0].type = VALUE_INTEGER;
    nested->values[0].data.integer = 20;
    nested->values[1].type = VALUE_INTEGER;
    nested->values[1].data.integer = 30;

    tuple->values[0].type = VALUE_INTEGER;
    tuple->values[0].data.integer = 10;
    tuple->values[1].type = VALUE_RECORD;
    tuple->values[1].data.record = nested;
    tuple->values[2].type = VALUE_INTEGER;
    tuple->values[2].data.integer = 40;

    if (record_remove_nested(tuple, 1U) != 0) {
        record_destroy(tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < tuple->count; ++i) {
        if (tuple->values[i].type == VALUE_INTEGER) {
            printf("%d\n", tuple->values[i].data.integer);
        }
    }

    record_destroy(tuple);
    return EXIT_SUCCESS;
}