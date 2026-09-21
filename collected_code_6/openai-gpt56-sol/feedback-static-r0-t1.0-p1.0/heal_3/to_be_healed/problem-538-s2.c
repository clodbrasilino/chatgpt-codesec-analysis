#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_list_to_tuple(const char *const list[],
                           const size_t item_sizes[],
                           size_t count)
{
    size_t length = 3;
    char *tuple;
    char *position;

    if (count != 0 && (list == NULL || item_sizes == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            return NULL;
        }

        if (item_sizes[i] > SIZE_MAX - length) {
            return NULL;
        }
        length += item_sizes[i];

        if (i + 1 < count) {
            if (length > SIZE_MAX - 2) {
                return NULL;
            }
            length += 2;
        }
    }

    tuple = malloc(length);
    if (tuple == NULL) {
        return NULL;
    }

    position = tuple;
    *position++ = '(';

    for (size_t i = 0; i < count; ++i) {
        size_t remaining = length - (size_t)(position - tuple);

        if (item_sizes[i] > remaining - 2) {
            free(tuple);
            return NULL;
        }

        if (item_sizes[i] != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(position, list[i], item_sizes[i]);
            position += item_sizes[i];
        }

        if (i + 1 < count) {
            if ((size_t)(position - tuple) > length - 3) {
                free(tuple);
                return NULL;
            }

            *position++ = ',';
            *position++ = ' ';
        }
    }

    *position++ = ')';
    *position = '\0';

    return tuple;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    const char *list[] = {apple, banana, cherry};
    const size_t item_sizes[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(cherry) - 1
    };
    const size_t count = sizeof(list) / sizeof(list[0]);
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