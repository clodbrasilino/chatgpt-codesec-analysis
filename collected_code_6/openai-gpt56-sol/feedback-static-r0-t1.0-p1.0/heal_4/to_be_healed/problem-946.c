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

static int compare_element_counts(const void *left, const void *right)
{
    const ElementCount *a = left;
    const ElementCount *b = right;

    if (a->count < b->count) {
        return 1;
    }
    if (a->count > b->count) {
        return -1;
    }
    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }

    return 0;
}

static int find_most_common_elements(const unsigned char *data,
                                     size_t data_length,
                                     ElementCount **results,
                                     size_t *result_count)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t maximum_count = 0;
    size_t output_count = 0;
    ElementCount *items;

    if ((data == NULL && data_length != 0) ||
        results == NULL ||
        result_count == NULL) {
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
            items[index].count = frequencies[i];
            ++index;
        }
    }

    qsort(items, output_count, sizeof(*items), compare_element_counts);

    *results = items;
    *result_count = output_count;
    return 0;
}

static int append_data(unsigned char **data,
                       size_t *length,
                       size_t *capacity,
                       const unsigned char *source,
                       size_t source_length)
{
    if (data == NULL || length == NULL || capacity == NULL ||
        (source == NULL && source_length != 0) ||
        (*data == NULL && *capacity != 0) ||
        *length > *capacity) {
        errno = EINVAL;
        return -1;
    }

    if (source_length > SIZE_MAX - *length) {
        errno = EOVERFLOW;
        return -1;
    }

    size_t required = *length + source_length;

    if (required > *capacity) {
        size_t new_capacity = *capacity != 0 ? *capacity : 256;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2;
        }

        if (new_capacity < required) {
            errno = EOVERFLOW;
            return -1;
        }

        unsigned char *resized = realloc(*data, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *data = resized;
        *capacity = new_capacity;
    }

    if (source_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*data + *length, source, source_length);
    }

    *length = required;
    return 0;
}

static int read_input(FILE *stream,
                      unsigned char **data,
                      size_t *length,
                      size_t *capacity)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char block[4096];

    if (stream == NULL || data == NULL || length == NULL || capacity == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (;;) {
        size_t bytes_read = fread(block, 1, sizeof(block), stream);

        if (bytes_read != 0 &&
            append_data(data, length, capacity, block, bytes_read) != 0) {
            return -1;
        }

        if (bytes_read < sizeof(block)) {
            if (ferror(stream)) {
                return -1;
            }

            if (feof(stream)) {
                return 0;
            }
        }
    }
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

    if (isprint((int)value) != 0) {
        return printf("'%c'", (int)value);
    }

    return printf("0x%02X", (unsigned int)value);
}

int main(void)
{
    unsigned char *data = NULL;
    ElementCount *results = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result_count = 0;
    int status = EXIT_FAILURE;

    if (read_input(stdin, &data, &length, &capacity) != 0) {
        perror("read_input");
        goto cleanup;
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

    if (fflush(stdout) == EOF) {
        perror("fflush");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(results);
    free(data);
    return status;
}