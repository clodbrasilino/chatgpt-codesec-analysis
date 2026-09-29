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
    size_t total_size = 1;
    char *result;
    char *position;

    if ((count > 0 && (elements == NULL || element_sizes == NULL)) ||
        (delimiter == NULL && delimiter_size != 0)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL && element_sizes[i] != 0) {
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

    result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    position = result;

    for (size_t i = 0; i < count; ++i) {
        if (element_sizes[i] != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(position, elements[i], element_sizes[i]);
            position += element_sizes[i];
        }

        if (i + 1 < count && delimiter_size != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(position, delimiter, delimiter_size);
            position += delimiter_size;
        }
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

    const char *tuple[] = {apple, banana, cherry};
    const size_t tuple_sizes[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(cherry) - 1
    };
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    char *joined = tuple_join(
        tuple,
        tuple_sizes,
        count,
        delimiter,
        sizeof(delimiter) - 1
    );

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