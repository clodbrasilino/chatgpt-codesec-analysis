#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

static int init_tuple(Tuple *tuple, const int *data, size_t size)
{
    if (tuple == NULL) {
        return -1;
    }
    tuple->data = NULL;
    tuple->size = 0;
    if (size == 0) {
        return 0;
    }
    if (data == NULL || size > SIZE_MAX / sizeof(*tuple->data)) {
        return -1;
    }
    tuple->data = (int *)malloc(size * sizeof(*tuple->data));
    if (tuple->data == NULL) {
        return -1;
    }
    memcpy(tuple->data, data, size * sizeof(*tuple->data));
    tuple->size = size;
    return 0;
}

static size_t remove_empty_tuples(Tuple *tuples, size_t count)
{
    size_t read_index;
    size_t write_index = 0;

    if (tuples == NULL) {
        return 0;
    }

    for (read_index = 0; read_index < count; read_index++) {
        if (tuples[read_index].data != NULL && tuples[read_index].size > 0) {
            if (write_index != read_index) {
                tuples[write_index] = tuples[read_index];
                tuples[read_index].data = NULL;
                tuples[read_index].size = 0;
            }
            write_index++;
        } else {
            free(tuples[read_index].data);
            tuples[read_index].data = NULL;
            tuples[read_index].size = 0;
        }
    }

    return write_index;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        printf("(");
        for (j = 0; j < tuples[i].size; j++) {
            printf("%d", tuples[i].data[j]);
            if (j + 1 < tuples[i].size) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("\n");
}

static void free_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(tuples[i].data);
        tuples[i].data = NULL;
        tuples[i].size = 0;
    }
    free(tuples);
}

int main(void)
{
    const size_t count = 6;
    size_t new_count;
    int values0[] = {1, 2, 3};
    int values2[] = {4, 5};
    int values4[] = {6, 7, 8, 9};
    Tuple *tuples = (Tuple *)calloc(count, sizeof(*tuples));

    if (tuples == NULL) {
        fprintf(stderr, "Error: failed to allocate tuple list\n");
        return EXIT_FAILURE;
    }

    if (init_tuple(&tuples[0], values0, 3) != 0 ||
        init_tuple(&tuples[1], NULL, 0) != 0 ||
        init_tuple(&tuples[2], values2, 2) != 0 ||
        init_tuple(&tuples[3], NULL, 0) != 0 ||
        init_tuple(&tuples[4], values4, 4) != 0 ||
        init_tuple(&tuples[5], NULL, 0) != 0) {
        fprintf(stderr, "Error: failed to initialize tuples\n");
        free_tuples(tuples, count);
        return EXIT_FAILURE;
    }

    printf("Original list of tuples:\n");
    print_tuples(tuples, count);

    new_count = remove_empty_tuples(tuples, count);

    printf("List after removing empty tuples:\n");
    print_tuples(tuples, new_count);

    free_tuples(tuples, count);
    return EXIT_SUCCESS;
}