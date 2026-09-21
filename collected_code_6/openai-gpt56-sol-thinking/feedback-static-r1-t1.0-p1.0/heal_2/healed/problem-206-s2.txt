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

static void free_string_array(owned_string *strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i].data);
    }

    free(strings);
}

static int concatenate_adjacent(const string_span *elements,
                                size_t element_count,
                                owned_string **result,
                                size_t *result_count)
{
    owned_string *concatenated;
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
        const size_t left_length = elements[i].length;
        const size_t right_length = elements[i + 1].length;
        size_t combined_length;
        char *destination;

        if (left_length > SIZE_MAX - right_length) {
            free_string_array(concatenated, adjacent_count);
            return EOVERFLOW;
        }

        combined_length = left_length + right_length;

        if (combined_length > SIZE_MAX - 1) {
            free_string_array(concatenated, adjacent_count);
            return EOVERFLOW;
        }

        destination = malloc(combined_length + 1);
        if (destination == NULL) {
            free_string_array(concatenated, adjacent_count);
            return ENOMEM;
        }

        concatenated[i].data = destination;
        concatenated[i].length = combined_length;

        for (size_t j = 0; j < left_length; ++j) {
            destination[j] = elements[i].data[j];
        }

        for (size_t j = 0; j < right_length; ++j) {
            destination[left_length + j] = elements[i + 1].data[j];
        }

        destination[combined_length] = '\0';
    }

    *result = concatenated;
    *result_count = adjacent_count;

    return 0;
}

static int print_tuple(const owned_string *elements, size_t count)
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

        if (elements[i].length != 0) {
            size_t written = fwrite(elements[i].data,
                                    1,
                                    elements[i].length,
                                    stdout);

            if (written != elements[i].length) {
                return EIO;
            }
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
    static const string_span tuple1[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"best", sizeof("best") - 1}
    };

    static const string_span tuple2[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"for", sizeof("for") - 1},
        {"geeks", sizeof("geeks") - 1}
    };

    static const string_span *const tuples[] = {
        tuple1,
        tuple2
    };

    static const size_t tuple_sizes[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0])
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    for (size_t i = 0; i < tuple_count; ++i) {
        owned_string *result = NULL;
        size_t result_count = 0;
        int status;

        status = concatenate_adjacent(tuples[i],
                                      tuple_sizes[i],
                                      &result,
                                      &result_count);

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
        int saved_errno = errno;
        fprintf(stderr, "Output failed: %s\n", strerror(saved_errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}