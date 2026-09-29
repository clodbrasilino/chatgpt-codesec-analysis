#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    char *data;
    size_t length;
} String;

void free_string_array(String *strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i].data);
    }

    free(strings);
}

static int copy_bytes(char *destination,
                      size_t destination_size,
                      const char *source,
                      size_t byte_count)
{
    if (byte_count == 0) {
        return 0;
    }

    if (destination == NULL || source == NULL) {
        return EINVAL;
    }

    if (byte_count > destination_size) {
        return EOVERFLOW;
    }

    for (size_t i = 0; i < byte_count; ++i) {
        destination[i] = source[i];
    }

    return 0;
}

int concatenate_adjacent(const StringView *elements,
                         size_t element_count,
                         String **result,
                         size_t *result_count)
{
    String *concatenated;
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
        size_t allocation_size;
        int status;

        if (left_length > SIZE_MAX - right_length) {
            free_string_array(concatenated, adjacent_count);
            return EOVERFLOW;
        }

        combined_length = left_length + right_length;

        if (combined_length == SIZE_MAX) {
            free_string_array(concatenated, adjacent_count);
            return EOVERFLOW;
        }

        allocation_size = combined_length + 1;
        concatenated[i].data = malloc(allocation_size);
        if (concatenated[i].data == NULL) {
            free_string_array(concatenated, adjacent_count);
            return ENOMEM;
        }

        status = copy_bytes(concatenated[i].data,
                            allocation_size,
                            elements[i].data,
                            left_length);
        if (status != 0) {
            free_string_array(concatenated, adjacent_count);
            return status;
        }

        status = copy_bytes(concatenated[i].data + left_length,
                            allocation_size - left_length,
                            elements[i + 1].data,
                            right_length);
        if (status != 0) {
            free_string_array(concatenated, adjacent_count);
            return status;
        }

        concatenated[i].data[combined_length] = '\0';
        concatenated[i].length = combined_length;
    }

    *result = concatenated;
    *result_count = adjacent_count;

    return 0;
}

int print_tuple(const String *elements, size_t count)
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
    static const StringView tuple1[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"best", sizeof("best") - 1}
    };

    static const StringView tuple2[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"for", sizeof("for") - 1},
        {"geeks", sizeof("geeks") - 1}
    };

    static const StringView *const tuples[] = {
        tuple1,
        tuple2
    };

    static const size_t tuple_sizes[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0])
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    for (size_t i = 0; i < tuple_count; ++i) {
        String *result = NULL;
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