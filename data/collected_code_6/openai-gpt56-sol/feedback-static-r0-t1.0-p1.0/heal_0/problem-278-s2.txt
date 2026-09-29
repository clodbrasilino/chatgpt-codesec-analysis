#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

int count_before_record(const Tuple *tuple, int record, size_t *count)
{
    if (tuple == NULL || count == NULL ||
        (tuple->length > 0 && tuple->elements == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->elements[i] == record) {
            *count = i;
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    Tuple tuple = {NULL, 0};
    size_t count = 0;
    int record = 0;

    if (scanf("%zu", &tuple.length) != 1) {
        return EXIT_FAILURE;
    }

    if (tuple.length > SIZE_MAX / sizeof(*tuple.elements)) {
        return EXIT_FAILURE;
    }

    if (tuple.length > 0) {
        tuple.elements = malloc(tuple.length * sizeof(*tuple.elements));
        if (tuple.elements == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < tuple.length; ++i) {
        if (scanf("%d", &tuple.elements[i]) != 1) {
            free(tuple.elements);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &record) != 1) {
        free(tuple.elements);
        return EXIT_FAILURE;
    }

    int status = count_before_record(&tuple, record, &count);

    if (status == 0) {
        printf("%zu\n", count);
    } else if (status == 1) {
        printf("-1\n");
    } else {
        free(tuple.elements);
        return EXIT_FAILURE;
    }

    free(tuple.elements);
    return EXIT_SUCCESS;
}