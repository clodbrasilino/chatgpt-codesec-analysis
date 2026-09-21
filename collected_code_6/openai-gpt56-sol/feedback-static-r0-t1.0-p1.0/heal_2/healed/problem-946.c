#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    ElementCount *items = NULL;

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

    output_count = 0;

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] == maximum_count) {
            items[output_count].value = (unsigned char)i;
            items[output_count].count = frequencies[i];
            ++output_count;
        }
    }

    qsort(items, output_count, sizeof(*items), compare_element_counts);

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

int main(void)
{
    unsigned char *data = NULL;
    ElementCount *results = NULL;
    size_t capacity = 256;
    size_t length = 0;
    size_t result_count = 0;
    int status = EXIT_FAILURE;

    data = malloc(capacity);
    if (data == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (;;) {
        unsigned char block[4096];
        size_t bytes_read = fread(block, 1, sizeof(block), stdin);

        if (bytes_read > 0) {
            if (length > SIZE_MAX - bytes_read) {
                errno = EOVERFLOW;
                perror("input");
                goto cleanup;
            }

            size_t required = length + bytes_read;

            if (required > capacity) {
                size_t new_capacity = capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                if (new_capacity < required) {
                    errno = EOVERFLOW;
                    perror("input");
                    goto cleanup;
                }

                unsigned char *resized_data = realloc(data, new_capacity);
                if (resized_data == NULL) {
                    perror("realloc");
                    goto cleanup;
                }

                data = resized_data;
                capacity = new_capacity;
            }

            for (size_t i = 0; i < bytes_read; ++i) {
                data[length + i] = block[i];
            }
            length = required;
        }

        if (bytes_read < sizeof(block)) {
            if (ferror(stdin)) {
                perror("fread");
                goto cleanup;
            }
            if (feof(stdin)) {
                break;
            }
        }
    }

    if (find_most_common_elements(data, length, &results, &result_count) != 0) {
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
    free(results);
    free(data);
    return status;
}