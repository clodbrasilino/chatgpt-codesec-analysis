#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_string_array(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

int concatenate_adjacent(const char *const *elements,
                         size_t element_count,
                         char ***result,
                         size_t *result_count)
{
    char **concatenated = NULL;
    size_t adjacent_count;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if (element_count != 0 && elements == NULL) {
        return EINVAL;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (elements[i] == NULL) {
            return EINVAL;
        }
    }

    if (element_count < 2) {
        return 0;
    }

    adjacent_count = element_count - 1;

    if (adjacent_count > SIZE_MAX / sizeof(*concatenated)) {
        return EOVERFLOW;
    }

    concatenated = calloc(adjacent_count, sizeof(*concatenated));
    if (concatenated == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < adjacent_count; ++i) {
        size_t left_length = strlen(elements[i]);
        size_t right_length = strlen(elements[i + 1]);
        size_t combined_length;

        if (left_length > SIZE_MAX - right_length) {
            free_string_array(concatenated, adjacent_count);
            return EOVERFLOW;
        }

        combined_length = left_length + right_length;

        if (combined_length == SIZE_MAX) {
            free_string_array(concatenated, adjacent_count);
            return EOVERFLOW;
        }

        concatenated[i] = malloc(combined_length + 1);
        if (concatenated[i] == NULL) {
            free_string_array(concatenated, adjacent_count);
            return ENOMEM;
        }

        memcpy(concatenated[i], elements[i], left_length);
        memcpy(concatenated[i] + left_length, elements[i + 1], right_length);
        concatenated[i][combined_length] = '\0';
    }

    *result = concatenated;
    *result_count = adjacent_count;

    return 0;
}

int print_tuple(char *const *elements, size_t count)
{
    if (elements == NULL && count != 0) {
        return EINVAL;
    }

    if (fputc('(', stdout) == EOF) {
        return EIO;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            return EINVAL;
        }

        if (i != 0 && fputs(", ", stdout) == EOF) {
            return EIO;
        }

        if (printf("\"%s\"", elements[i]) < 0) {
            return EIO;
        }
    }

    if (fputs(")\n", stdout) == EOF) {
        return EIO;
    }

    return 0;
}

int main(void)
{
    const char *const tuple1[] = {"GFG", "is", "best"};
    const char *const tuple2[] = {"GFG", "is", "for", "geeks"};
    const char *const *const tuples[] = {tuple1, tuple2};
    const size_t tuple_sizes[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0])
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    for (size_t i = 0; i < tuple_count; ++i) {
        char **result = NULL;
        size_t result_count = 0;
        int status = concatenate_adjacent(
            tuples[i],
            tuple_sizes[i],
            &result,
            &result_count
        );

        if (status != 0) {
            fprintf(stderr, "Concatenation failed: %s\n", strerror(status));
            free_string_array(result, result_count);
            return EXIT_FAILURE;
        }

        status = print_tuple(result, result_count);
        free_string_array(result, result_count);

        if (status != 0) {
            fprintf(stderr, "Output failed: %s\n", strerror(status));
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}