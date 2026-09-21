#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *tuple_join(const char *const elements[],
                 const size_t element_sizes[],
                 size_t count,
                 const char *delimiter,
                 size_t delimiter_size)
{
    if ((count != 0 && (elements == NULL || element_sizes == NULL)) ||
        (delimiter_size != 0 && delimiter == NULL)) {
        return NULL;
    }

    size_t total_size = 1;

    for (size_t i = 0; i < count; ++i) {
        if (element_sizes[i] != 0 && elements[i] == NULL) {
            return NULL;
        }

        if (element_sizes[i] > SIZE_MAX - total_size) {
            return NULL;
        }
        total_size += element_sizes[i];

        if (i + 1 < count) {
            if (delimiter_size > SIZE_MAX - total_size) {
                return NULL;
            }
            total_size += delimiter_size;
        }
    }

    char *result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    char *position = result;
    size_t remaining = total_size;

    for (size_t i = 0; i < count; ++i) {
        if (element_sizes[i] != 0) {
            if (element_sizes[i] >= remaining) {
                free(result);
                return NULL;
            }

            memcpy(position, elements[i], element_sizes[i]);
            position += element_sizes[i];
            remaining -= element_sizes[i];
        }

        if (i + 1 < count && delimiter_size != 0) {
            if (delimiter_size >= remaining) {
                free(result);
                return NULL;
            }

            memcpy(position, delimiter, delimiter_size);
            position += delimiter_size;
            remaining -= delimiter_size;
        }
    }

    if (remaining == 0) {
        free(result);
        return NULL;
    }

    *position = '\0';
    return result;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char delimiter[] = ", ";

    const char *tuple[] = {
        apple,
        banana,
        cherry
    };

    const size_t tuple_sizes[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(cherry) - 1
    };

    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    char *joined = tuple_join(tuple,
                              tuple_sizes,
                              count,
                              delimiter,
                              sizeof(delimiter) - 1);

    if (joined == NULL) {
        fputs("Failed to concatenate tuple elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}