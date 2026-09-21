#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(const char *elements[], size_t count, const char *delimiter) {
    if (elements == NULL && count > 0) {
        return NULL;
    }
    if (delimiter == NULL) {
        delimiter = "";
    }

    size_t total = 1;
    size_t delim_len = strlen(delimiter);

    for (size_t i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            return NULL;
        }
        size_t elem_len = strlen(elements[i]);
        if (total > SIZE_MAX - elem_len) {
            return NULL;
        }
        total += elem_len;
        if (i < count - 1) {
            if (total > SIZE_MAX - delim_len) {
                return NULL;
            }
            total += delim_len;
        }
    }

    char *result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    char *dest = result;
    size_t space = total;
    for (size_t i = 0; i < count; i++) {
        int written = snprintf(dest, space, "%s", elements[i]);
        if (written < 0 || (size_t)written >= space) {
            free(result);
            return NULL;
        }
        dest += written;
        space -= written;

        if (i < count - 1) {
            written = snprintf(dest, space, "%s", delimiter);
            if (written < 0 || (size_t)written >= space) {
                free(result);
                return NULL;
            }
            dest += written;
            space -= written;
        }
    }

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    char *joined = concat_tuple(tuple, 3, ", ");
    if (joined == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);

    return EXIT_SUCCESS;
}