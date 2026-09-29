#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

int create_tuple(Tuple *t, const int *values, size_t length)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (t == NULL || (values == NULL && length > 0U)) {
        return -1;
    }

    t->elements = NULL;
    t->length = 0U;

    if (length > 0U) {
        if (length > SIZE_MAX / sizeof(int)) {
            return -1;
        }
        t->elements = malloc(length * sizeof(int));
        if (t->elements == NULL) {
            return -1;
        }
        for (i = 0U; i < length; i++) {
            t->elements[i] = values[i];
        }
        t->length = length;
    }

    return 0;
}

void destroy_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->length = 0U;
    }
}

size_t remove_tuples_with_length_k(Tuple *tuples, size_t count, size_t k)
{
    size_t write_index = 0U;
    size_t read_index;

    if (tuples == NULL) {
        return 0U;
    }

    for (read_index = 0U; read_index < count; read_index++) {
        if (tuples[read_index].length == k) {
            destroy_tuple(&tuples[read_index]);
        } else {
            if (write_index != read_index) {
                tuples[write_index] = tuples[read_index];
                tuples[read_index].elements = NULL;
                tuples[read_index].length = 0U;
            }
            write_index++;
        }
    }

    return write_index;
}

void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return;
    }

    printf("[");
    for (i = 0U; i < count; i++) {
        printf("(");
        for (j = 0U; j < tuples[i].length; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j + 1U < tuples[i].length) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1U < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    Tuple tuples[5];
    size_t count = 5U;
    size_t i;
    size_t k = 2U;

    static const int data0[] = {4, 5};
    static const int data1[] = {4};
    static const int data2[] = {8, 6, 7};
    static const int data3[] = {1, 2};
    static const int data4[] = {3, 4, 6, 7};

    memset(tuples, 0, sizeof(tuples));

    if (create_tuple(&tuples[0], data0, 2U) != 0 ||
        create_tuple(&tuples[1], data1, 1U) != 0 ||
        create_tuple(&tuples[2], data2, 3U) != 0 ||
        create_tuple(&tuples[3], data3, 2U) != 0 ||
        create_tuple(&tuples[4], data4, 4U) != 0) {
        for (i = 0U; i < count; i++) {
            destroy_tuple(&tuples[i]);
        }
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original tuples: ");
    print_tuples(tuples, count);

    count = remove_tuples_with_length_k(tuples, count, k);

    printf("After removing tuples of length %zu: ", k);
    print_tuples(tuples, count);

    for (i = 0U; i < count; i++) {
        destroy_tuple(&tuples[i]);
    }

    return EXIT_SUCCESS;
}