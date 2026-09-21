#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} string_span;

typedef struct {
    char *data;
    size_t length;
} owned_string;

void free_string_array(owned_string *strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i].data);
    }

    free(strings);
}

int concatenate_adjacent(const string_span *elements,
                         size_t element_count,
                         owned_string **result,
                         size_t *result_count)
{
    owned_string *concatenated = NULL;
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
        if (elements[i].data == NULL) {
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
        size_t left_length = elements[i].length;
        size_t right_length = elements[i + 1].length;
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

        concatenated[i].data = malloc(combined_length + 1);
        if (concatenated[i].data == NULL) {
            free_string_array(concatenated, adjacent_count);
            return ENOMEM;
        }

        if (left_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(concatenated[i].data, elements[i].data, left_length);
        }

        if (right_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(concatenated[i].data + left_length,
                   elements[i + 1].data,
                   right_length);
        }

        concatenated[i].data[combined_length] = '\0';
        concatenated[i].length = combined_length;
    }

    *result = concatenated;
    *result_count = adjacent_count;

    return 0;
}

int print_tuple(const owned_string *elements, size_t count)
{
    if (count != 0 && elements == NULL) {
        return EINVAL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].data == NULL) {
            return EINVAL;
        }
    }

    if (fputc('(', stdout) == EOF) {
        return EIO;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return EIO;
        }

        if (fputc('"', stdout) == EOF) {
            return EIO;
        }

        if (elements[i].length != 0 &&
            fwrite(elements[i].data, 1, elements[i].length, stdout) !=
                elements[i].length) {
            return EIO;
        }

        if (fputc('"', stdout) == EOF) {
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
    const string_span tuple1[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"best", sizeof("best") - 1}
    };

    const string_span tuple2[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"for", sizeof("for") - 1},
        {"geeks", sizeof("geeks") - 1}
    };

    const string_span *const tuples[] = {
        tuple1,
        tuple2
    };

    const size_t tuple_sizes[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0])
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    for (size_t i = 0; i < tuple_count; ++i) {
        owned_string *result = NULL;
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

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Output failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}