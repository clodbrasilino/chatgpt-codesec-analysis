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

static int find_most_common_elements(FILE *stream,
                                     ElementCount **results,
                                     size_t *result_count)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t maximum_count = 0;
    size_t output_count = 0;
    ElementCount *items = NULL;
    unsigned char *block = NULL;
    const size_t block_size = 4096;

    if (stream == NULL || results == NULL || result_count == NULL) {
        errno = EINVAL;
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    block = malloc(block_size);
    if (block == NULL) {
        return -1;
    }

    for (;;) {
        size_t bytes_read = fread(block, 1, block_size, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            unsigned char value = block[i];

            if (frequencies[value] == SIZE_MAX) {
                free(block);
                errno = EOVERFLOW;
                return -1;
            }

            ++frequencies[value];

            if (frequencies[value] > maximum_count) {
                maximum_count = frequencies[value];
            }
        }

        if (bytes_read < block_size) {
            if (ferror(stream)) {
                int saved_errno = errno != 0 ? errno : EIO;
                free(block);
                errno = saved_errno;
                return -1;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    free(block);

    if (maximum_count == 0) {
        return 0;
    }

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
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

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
        if (frequencies[i] == maximum_count) {
            items[index].value = (unsigned char)i;
            items[index].count = frequencies[i];
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

    if (isprint(value)) {
        return printf("'%c'", (int)value);
    }

    return printf("0x%02X", (unsigned int)value);
}

int main(void)
{
    ElementCount *results = NULL;
    size_t result_count = 0;
    int status = EXIT_FAILURE;

    if (find_most_common_elements(stdin, &results, &result_count) != 0) {
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
    return status;
}