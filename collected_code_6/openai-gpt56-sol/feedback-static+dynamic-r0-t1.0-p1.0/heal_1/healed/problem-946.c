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
    ElementCount *items;

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
            items[index].count = frequencies[i];
            ++index;
        }
    }

    qsort(items, output_count, sizeof(*items), compare_element_counts);

    *results = items;
    *result_count = output_count;
    return 0;
}

static int print_element(unsigned char value)
{
    if (value == '\n') {
        return printf("'\\n'");
    }
    if (value == '\r') {
        return printf("'\\r'");
    }
    if (value == '\t') {
        return printf("'\\t'");
    }
    if (value == '\\') {
        return printf("'\\\\'");
    }
    if (value == '\'') {
        return printf("'\\''");
    }
    if (isprint((int)value) != 0) {
        return printf("'%c'", (int)value);
    }

    return printf("0x%02X", (unsigned int)value);
}

int main(void)
{
    unsigned char *data = NULL;
    size_t capacity = 256;
    size_t length = 0;
    ElementCount *results = NULL;
    size_t result_count = 0;
    int status = EXIT_FAILURE;

    data = malloc(capacity);
    if (data == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (;;) {
        int input = fgetc(stdin);

        if (input == EOF) {
            if (ferror(stdin)) {
                perror("fgetc");
                goto cleanup;
            }
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *resized_data;

            if (capacity > SIZE_MAX / 2) {
                errno = EOVERFLOW;
                perror("input");
                goto cleanup;
            }

            new_capacity = capacity * 2;
            resized_data = realloc(data, new_capacity);

            if (resized_data == NULL) {
                perror("realloc");
                goto cleanup;
            }

            data = resized_data;
            capacity = new_capacity;
        }

        data[length++] = (unsigned char)input;
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