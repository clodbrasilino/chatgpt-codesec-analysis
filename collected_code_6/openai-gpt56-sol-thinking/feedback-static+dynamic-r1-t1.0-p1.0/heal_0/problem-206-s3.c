#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *const *elements;
    size_t count;
} Tuple;

static void free_string_array(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int concatenate_adjacent(const Tuple *tuple, char ***result,
                                size_t *result_count)
{
    char **concatenated = NULL;
    size_t adjacent_count;

    if (tuple == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (tuple->count > 0 && tuple->elements == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->elements[i] == NULL) {
            return -1;
        }
    }

    if (tuple->count < 2) {
        return 0;
    }

    adjacent_count = tuple->count - 1;

    if (adjacent_count > SIZE_MAX / sizeof(*concatenated)) {
        return -1;
    }

    concatenated = calloc(adjacent_count, sizeof(*concatenated));
    if (concatenated == NULL) {
        return -1;
    }

    for (size_t i = 0; i < adjacent_count; ++i) {
        size_t first_length = strlen(tuple->elements[i]);
        size_t second_length = strlen(tuple->elements[i + 1]);
        size_t combined_length;

        if (first_length > SIZE_MAX - second_length) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        combined_length = first_length + second_length;

        if (combined_length == SIZE_MAX) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        concatenated[i] = malloc(combined_length + 1);
        if (concatenated[i] == NULL) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        memcpy(concatenated[i], tuple->elements[i], first_length);
        memcpy(concatenated[i] + first_length,
               tuple->elements[i + 1],
               second_length + 1);
    }

    *result = concatenated;
    *result_count = adjacent_count;
    return 0;
}

static int print_string_tuple(char *const *strings, size_t count)
{
    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("\"%s\"", strings[i]) < 0) {
            return -1;
        }
    }

    if (puts(")") == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *first_elements[] = {
        "GFG", "is", "best", "for", "geeks"
    };
    const char *second_elements[] = {
        "C", "programming", "is", "powerful"
    };
    const Tuple tuples[] = {
        {first_elements, sizeof(first_elements) / sizeof(first_elements[0])},
        {second_elements, sizeof(second_elements) / sizeof(second_elements[0])}
    };

    for (size_t i = 0; i < sizeof(tuples) / sizeof(tuples[0]); ++i) {
        char **result = NULL;
        size_t result_count = 0;

        if (concatenate_adjacent(&tuples[i], &result, &result_count) != 0) {
            fputs("Failed to concatenate tuple elements.\n", stderr);
            return EXIT_FAILURE;
        }

        if (print_string_tuple(result, result_count) != 0) {
            free_string_array(result, result_count);
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }

        free_string_array(result, result_count);
    }

    return EXIT_SUCCESS;
}