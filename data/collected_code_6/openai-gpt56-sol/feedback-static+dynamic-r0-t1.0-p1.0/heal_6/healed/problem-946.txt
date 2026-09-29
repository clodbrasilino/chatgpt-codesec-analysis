#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char value;
    size_t count;
} ElementCount;

static int find_most_common_elements(const unsigned char *data,
                                     size_t data_length,
                                     ElementCount **results,
                                     size_t *result_count)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t maximum_count = 0;
    size_t output_count = 0;
    ElementCount *items = NULL;

    if (results == NULL || result_count == NULL ||
        (data == NULL && data_length != 0)) {
        errno = EINVAL;
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    for (size_t i = 0; i < data_length; ++i) {
        unsigned char value = data[i];

        if (frequencies[value] == SIZE_MAX) {
            errno = EOVERFLOW;
            return -1;
        }

        ++frequencies[value];

        if (frequencies[value] > maximum_count) {
            maximum_count = frequencies[value];
        }
    }

    if (maximum_count == 0) {
        return 0;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] == maximum_count) {
            ++output_count;
        }
    }

    if (output_count > SIZE_MAX / sizeof(*items)) {
        errno = EOVERFLOW;
        return -1;
    }

    items = malloc(output_count * sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    size_t index = 0;

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] == maximum_count) {
            items[index].value = (unsigned char)i;
            items[index].count = maximum_count;
            ++index;
        }
    }

    *results = items;
    *result_count = output_count;
    return 0;
}

static int print_element(unsigned char value)
{
    switch (value) {
        case '\n':
            return printf("'\\n'");
        case '\r':
            return printf("'\\r'");
        case '\t':
            return printf("'\\t'");
        case '\\':
            return printf("'\\\\'");
        case '\'':
            return printf("'\\''");
        default:
            break;
    }

    if (isprint((int)value)) {
        return printf("'%c'", (int)value);
    }

    return printf("0x%02X", (unsigned int)value);
}

static int append_data(unsigned char **data,
                       size_t *length,
                       size_t *capacity,
                       const unsigned char *source,
                       size_t source_length)
{
    size_t required;
    size_t new_capacity;
    unsigned char *resized;

    if (data == NULL || length == NULL || capacity == NULL ||
        (source == NULL && source_length != 0) ||
        *length > *capacity ||
        (*data == NULL && *capacity != 0)) {
        errno = EINVAL;
        return -1;
    }

    if (source_length == 0) {
        return 0;
    }

    if (source_length > SIZE_MAX - *length) {
        errno = EOVERFLOW;
        return -1;
    }

    required = *length + source_length;

    if (required > *capacity) {
        new_capacity = (*capacity == 0) ? 4096U : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2U) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2U;
        }

        resized = realloc(*data, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *data = resized;
        *capacity = new_capacity;
    }

    if (*data == NULL || *length > *capacity ||
        source_length > *capacity - *length) {
        errno = EOVERFLOW;
        return -1;
    }

    memmove(*data + *length, source, source_length);
    *length = required;
    return 0;
}

int main(void)
{
    unsigned char *data = NULL;
    unsigned char *input_buffer = NULL;
    ElementCount *results = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result_count = 0;
    const size_t input_buffer_size = 4096U;
    int status = EXIT_FAILURE;

    input_buffer = malloc(input_buffer_size);
    if (input_buffer == NULL) {
        perror("malloc");
        goto cleanup;
    }

    for (;;) {
        size_t bytes_read = fread(input_buffer, 1, input_buffer_size, stdin);

        if (bytes_read > 0 &&
            append_data(&data, &length, &capacity,
                        input_buffer, bytes_read) != 0) {
            perror("input");
            goto cleanup;
        }

        if (bytes_read < input_buffer_size) {
            if (ferror(stdin)) {
                perror("fread");
                goto cleanup;
            }
            break;
        }
    }

    if (find_most_common_elements(data, length,
                                  &results, &result_count) != 0) {
        perror("find_most_common_elements");
        goto cleanup;
    }

    if (result_count == 0) {
        if (printf("No elements found.\n") < 0) {
            perror("printf");
            goto cleanup;
        }
    } else {
        for (size_t i = 0; i < result_count; ++i) {
            if (print_element(results[i].value) < 0 ||
                printf(": %zu\n", results[i].count) < 0) {
                perror("printf");
                goto cleanup;
            }
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input_buffer);
    free(results);
    free(data);
    return status;
}