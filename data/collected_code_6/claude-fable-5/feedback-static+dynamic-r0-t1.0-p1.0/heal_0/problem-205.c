#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple *invert_tuples(const Tuple *tuples, size_t count)
{
    Tuple *result;
    size_t i;

    if (tuples == NULL || count == 0U) {
        return NULL;
    }

    result = (Tuple *)malloc(count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        result[i].first = ~tuples[i].first;
        result[i].second = ~tuples[i].second;
    }

    return result;
}

int main(void)
{
    Tuple input[] = { {7, 8}, {9, 11}, {10, 15}, {0, -1} };
    size_t count = sizeof(input) / sizeof(input[0]);
    Tuple *inverted;
    size_t i;

    inverted = invert_tuples(input, count);
    if (inverted == NULL) {
        fprintf(stderr, "Failed to invert tuples\n");
        return EXIT_FAILURE;
    }

    printf("Original tuples:\n");
    for (i = 0U; i < count; i++) {
        printf("(%d, %d)\n", input[i].first, input[i].second);
    }

    printf("Inverted tuples:\n");
    for (i = 0U; i < count; i++) {
        printf("(%d, %d)\n", inverted[i].first, inverted[i].second);
    }

    free(inverted);
    return EXIT_SUCCESS;
}