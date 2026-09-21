#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

char **extract_strings(const char *const *list, size_t list_size, size_t count)
{
    char **result;
    size_t i;

    if (list == NULL || count == 0 || count > list_size) {
        return NULL;
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;
        size_t buf_size;
        int written;

        if (list[i] == NULL) {
            continue;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);
        buf_size = len + 1;

        if (buf_size > (size_t)MAX_STRING_LENGTH + 1) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        result[i] = malloc(buf_size);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        written = snprintf(result[i], buf_size, "%.*s", (int)len, list[i]);
        if (written < 0 || (size_t)written >= buf_size) {
            size_t j;
            for (j = 0; j <= i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    return result;
}

void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void)
{
    const char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const size_t list_size = sizeof(list) / sizeof(list[0]);
    const size_t count = 3;
    char **extracted;
    size_t i;

    extracted = extract_strings(list, list_size, count);
    if (extracted == NULL) {
        fprintf(stderr, "Error: failed to extract strings\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (extracted[i] != NULL) {
            printf("%s\n", extracted[i]);
        }
    }

    free_strings(extracted, count);

    return EXIT_SUCCESS;
}