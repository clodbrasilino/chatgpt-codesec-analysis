#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_list_to_tuple(const char *const list[],
                           const size_t item_sizes[],
                           size_t count)
{
    size_t content_size = 0;
    size_t separator_size = 0;
    size_t total_size;
    size_t used = 0;
    char *tuple;

    if (count != 0 && (list == NULL || item_sizes == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            return NULL;
        }

        if (item_sizes[i] > SIZE_MAX - content_size) {
            return NULL;
        }

        content_size += item_sizes[i];
    }

    if (count > 1) {
        if (count - 1 > SIZE_MAX / 2) {
            return NULL;
        }

        separator_size = (count - 1) * 2;
    }

    if (content_size > SIZE_MAX - separator_size) {
        return NULL;
    }

    total_size = content_size + separator_size;

    if (total_size > SIZE_MAX - 3) {
        return NULL;
    }

    total_size += 3;

    tuple = malloc(total_size);
    if (tuple == NULL) {
        return NULL;
    }

    tuple[used++] = '(';

    for (size_t i = 0; i < count; ++i) {
        size_t remaining = total_size - used;

        if (item_sizes[i] > remaining - 2) {
            free(tuple);
            return NULL;
        }

        if (item_sizes[i] != 0) {
            memcpy(tuple + used, list[i], item_sizes[i]);
            used += item_sizes[i];
        }

        if (i + 1 < count) {
            if (total_size - used < 4) {
                free(tuple);
                return NULL;
            }

            tuple[used++] = ',';
            tuple[used++] = ' ';
        }
    }

    if (total_size - used != 2) {
        free(tuple);
        return NULL;
    }

    tuple[used++] = ')';
    tuple[used] = '\0';

    return tuple;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    const char *const list[] = {apple, banana, cherry};
    const size_t item_sizes[] = {
        sizeof apple - 1,
        sizeof banana - 1,
        sizeof cherry - 1
    };
    const size_t count = sizeof list / sizeof list[0];
    char *tuple = string_list_to_tuple(list, item_sizes, count);

    if (tuple == NULL) {
        fputs("Failed to create tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", tuple) < 0) {
        free(tuple);
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}