#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int zip_tuples(const int *first, size_t first_length,
                      const int *second, size_t second_length,
                      Pair **result, size_t *result_length)
{
    size_t length;
    Pair *pairs;

    if (result == NULL || result_length == NULL) {
        return -1;
    }

    *result = NULL;
    *result_length = 0;

    if ((first == NULL && first_length != 0) ||
        (second == NULL && second_length != 0)) {
        return -1;
    }

    length = first_length < second_length ? first_length : second_length;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*pairs)) {
        return -1;
    }

    pairs = malloc(length * sizeof(*pairs));
    if (pairs == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        pairs[i].first = first[i];
        pairs[i].second = second[i];
    }

    *result = pairs;
    *result_length = length;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4};
    const int second[] = {10, 20, 30};
    Pair *zipped = NULL;
    size_t zipped_length = 0;

    if (zip_tuples(first, sizeof(first) / sizeof(first[0]),
                   second, sizeof(second) / sizeof(second[0]),
                   &zipped, &zipped_length) != 0) {
        fputs("Failed to zip tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < zipped_length; ++i) {
        if (printf("(%d, %d)%s",
                   zipped[i].first,
                   zipped[i].second,
                   i + 1 == zipped_length ? "\n" : ", ") < 0) {
            free(zipped);
            return EXIT_FAILURE;
        }
    }

    free(zipped);
    return EXIT_SUCCESS;
}