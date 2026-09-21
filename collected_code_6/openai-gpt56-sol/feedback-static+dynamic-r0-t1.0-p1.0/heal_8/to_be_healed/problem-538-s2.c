#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_list_to_tuple(const char *const list[],
                           const size_t lengths[],
                           size_t count)
{
    size_t content_size = 0;
    size_t separator_size = 0;
    size_t total_size;
    char *tuple;
    char *position;

    if (count != 0 && (list == NULL || lengths == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            return NULL;
        }

        if (content_size > SIZE_MAX - lengths[i]) {
            return NULL;
        }

        content_size += lengths[i];
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

    position = tuple;
    *position++ = '(';

    for (size_t i = 0; i < count; ++i) {
        size_t used = (size_t)(position - tuple);
        size_t available = total_size - used;

        if (lengths[i] > available) {
            free(tuple);
            return NULL;
        }

        if (lengths[i] != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(position, list[i], lengths[i]);
            position += lengths[i];
        }

        if (i + 1 < count) {
            used = (size_t)(position - tuple);
            available = total_size - used;

            if (available < 2) {
                free(tuple);
                return NULL;
            }

            *position++ = ',';
            *position++ = ' ';
        }
    }

    if ((size_t)(position - tuple) > total_size - 2) {
        free(tuple);
        return NULL;
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

    const char *list[] = {
        apple,
        banana,
        cherry
    };

    const size_t lengths[] = {
        sizeof apple - 1,
        sizeof banana - 1,
        sizeof cherry - 1
    };

    const size_t count = sizeof list / sizeof list[0];
    char *tuple = string_list_to_tuple(list, lengths, count);

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