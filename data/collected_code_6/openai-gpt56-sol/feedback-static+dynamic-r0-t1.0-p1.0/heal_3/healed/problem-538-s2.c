#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_list_to_tuple(const char *const list[],
                           const size_t lengths[],
                           size_t count)
{
    size_t total = 3;
    char *tuple;
    char *position;
    size_t remaining;

    if (count != 0 && (list == NULL || lengths == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - total) {
            return NULL;
        }
        total += lengths[i];

        if (i + 1 < count) {
            if (total > SIZE_MAX - 2) {
                return NULL;
            }
            total += 2;
        }
    }

    tuple = malloc(total);
    if (tuple == NULL) {
        return NULL;
    }

    position = tuple;
    remaining = total;

    *position++ = '(';
    --remaining;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] > remaining) {
            free(tuple);
            return NULL;
        }

        if (lengths[i] != 0) {
            memcpy(position, list[i], lengths[i]);
            position += lengths[i];
            remaining -= lengths[i];
        }

        if (i + 1 < count) {
            if (remaining < 2) {
                free(tuple);
                return NULL;
            }

            *position++ = ',';
            *position++ = ' ';
            remaining -= 2;
        }
    }

    if (remaining != 2) {
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