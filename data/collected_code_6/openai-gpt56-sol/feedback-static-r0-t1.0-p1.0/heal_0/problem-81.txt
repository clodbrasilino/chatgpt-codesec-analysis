#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int zip_tuples(const int *first, size_t first_len,
                      const int *second, size_t second_len,
                      Pair **result, size_t *result_len)
{
    Pair *pairs;
    size_t count;

    if (result == NULL || result_len == NULL) {
        return -1;
    }

    *result = NULL;
    *result_len = 0;

    if ((first == NULL && first_len != 0) ||
        (second == NULL && second_len != 0)) {
        return -1;
    }

    count = first_len < second_len ? first_len : second_len;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*pairs)) {
        return -1;
    }

    pairs = malloc(count * sizeof(*pairs));
    if (pairs == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        pairs[i].first = first[i];
        pairs[i].second = second[i];
    }

    *result = pairs;
    *result_len = count;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    Pair *zipped = NULL;
    size_t zipped_len = 0;

    if (zip_tuples(first, sizeof(first) / sizeof(first[0]),
                   second, sizeof(second) / sizeof(second[0]),
                   &zipped, &zipped_len) != 0) {
        fputs("Failed to zip tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < zipped_len; ++i) {
        if (printf("(%d, %d)%s",
                   zipped[i].first,
                   zipped[i].second,
                   i + 1 == zipped_len ? "\n" : ", ") < 0) {
            free(zipped);
            return EXIT_FAILURE;
        }
    }

    free(zipped);
    return EXIT_SUCCESS;
}