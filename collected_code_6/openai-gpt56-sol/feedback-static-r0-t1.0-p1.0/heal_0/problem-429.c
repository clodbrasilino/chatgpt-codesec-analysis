#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    size_t size;
} PairTuple;

static int elementwise_and(const Tuple *left, const Tuple *right, PairTuple *result)
{
    size_t i;

    if (left == NULL || right == NULL || result == NULL ||
        (left->size > 0U && left->elements == NULL) ||
        (right->size > 0U && right->elements == NULL) ||
        left->size != right->size) {
        return 0;
    }

    result->pairs = NULL;
    result->size = 0U;

    if (left->size == 0U) {
        return 1;
    }

    if (left->size > SIZE_MAX / sizeof(*result->pairs)) {
        return 0;
    }

    result->pairs = malloc(left->size * sizeof(*result->pairs));
    if (result->pairs == NULL) {
        return 0;
    }

    for (i = 0U; i < left->size; ++i) {
        result->pairs[i].first = left->elements[i];
        result->pairs[i].second = right->elements[i];
    }

    result->size = left->size;
    return 1;
}

static void free_pair_tuple(PairTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->pairs);
        tuple->pairs = NULL;
        tuple->size = 0U;
    }
}

static void print_pair_tuple(const PairTuple *tuple)
{
    size_t i;

    if (tuple == NULL || (tuple->size > 0U && tuple->pairs == NULL)) {
        return;
    }

    putchar('(');
    for (i = 0U; i < tuple->size; ++i) {
        if (i != 0U) {
            printf(", ");
        }
        printf("(%d, %d)", tuple->pairs[i].first, tuple->pairs[i].second);
    }
    puts(")");
}

int main(void)
{
    int first_elements[] = {1, 2, 3, 4};
    int second_elements[] = {5, 6, 7, 8};
    Tuple first = {first_elements, sizeof(first_elements) / sizeof(first_elements[0])};
    Tuple second = {second_elements, sizeof(second_elements) / sizeof(second_elements[0])};
    PairTuple result = {NULL, 0U};

    if (!elementwise_and(&first, &second, &result)) {
        fputs("Failed to combine tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    print_pair_tuple(&result);
    free_pair_tuple(&result);

    return EXIT_SUCCESS;
}