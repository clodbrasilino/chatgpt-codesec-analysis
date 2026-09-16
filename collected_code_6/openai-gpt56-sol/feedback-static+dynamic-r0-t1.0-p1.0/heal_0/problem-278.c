#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int count_before_record(const Tuple *tuple, int record, size_t *count)
{
    if (tuple == NULL || count == NULL ||
        (tuple->elements == NULL && tuple->size != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < tuple->size; ++i) {
        if (tuple->elements[i] == record) {
            *count = i;
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int values[] = {10, 20, 30, 40, 50};
    Tuple tuple = {
        .elements = values,
        .size = sizeof(values) / sizeof(values[0])
    };
    size_t count = 0U;
    int record = 40;
    int result = count_before_record(&tuple, record, &count);

    if (result == 0) {
        printf("%zu\n", count);
        return EXIT_SUCCESS;
    }

    if (result == 1) {
        fprintf(stderr, "Record not found\n");
    } else {
        fprintf(stderr, "Invalid argument\n");
    }

    return EXIT_FAILURE;
}