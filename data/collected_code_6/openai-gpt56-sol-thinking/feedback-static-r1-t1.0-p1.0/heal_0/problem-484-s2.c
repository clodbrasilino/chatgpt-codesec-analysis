#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

static bool read_tuple(Tuple *tuple)
{
    if (tuple == NULL || scanf("%zu", &tuple->length) != 1) {
        return false;
    }

    tuple->values = NULL;

    if (tuple->length == 0) {
        return true;
    }

    if (tuple->length > SIZE_MAX / sizeof(*tuple->values)) {
        return false;
    }

    tuple->values = malloc(tuple->length * sizeof(*tuple->values));
    if (tuple->values == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (scanf("%d", &tuple->values[i]) != 1) {
            free(tuple->values);
            tuple->values = NULL;
            tuple->length = 0;
            return false;
        }
    }

    return true;
}

static bool remove_matching(Tuple *first, Tuple *second)
{
    if (first == NULL || second == NULL || first == second ||
        (first->length != 0 && first->values == NULL) ||
        (second->length != 0 && second->values == NULL) ||
        (first->length != 0 && first->values == second->values)) {
        return false;
    }

    if (first->length == 0 || second->length == 0) {
        return true;
    }

    bool *matched = calloc(second->length, sizeof(*matched));
    if (matched == NULL) {
        return false;
    }

    size_t first_write = 0;

    for (size_t i = 0; i < first->length; ++i) {
        size_t j;

        for (j = 0; j < second->length; ++j) {
            if (!matched[j] && first->values[i] == second->values[j]) {
                matched[j] = true;
                break;
            }
        }

        if (j == second->length) {
            first->values[first_write++] = first->values[i];
        }
    }

    size_t second_write = 0;

    for (size_t i = 0; i < second->length; ++i) {
        if (!matched[i]) {
            second->values[second_write++] = second->values[i];
        }
    }

    first->length = first_write;
    second->length = second_write;

    free(matched);
    return true;
}

static void print_tuple(const Tuple *tuple)
{
    putchar('(');

    for (size_t i = 0; i < tuple->length; ++i) {
        if (i != 0) {
            printf(", ");
        }

        printf("%d", tuple->values[i]);
    }

    if (tuple->length == 1) {
        putchar(',');
    }

    puts(")");
}

static void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->length = 0;
    }
}

int main(void)
{
    Tuple first = {NULL, 0};
    Tuple second = {NULL, 0};

    if (!read_tuple(&first) || !read_tuple(&second)) {
        free_tuple(&first);
        free_tuple(&second);
        return EXIT_FAILURE;
    }

    if (!remove_matching(&first, &second)) {
        free_tuple(&first);
        free_tuple(&second);
        return EXIT_FAILURE;
    }

    print_tuple(&first);
    print_tuple(&second);

    free_tuple(&first);
    free_tuple(&second);

    return EXIT_SUCCESS;
}