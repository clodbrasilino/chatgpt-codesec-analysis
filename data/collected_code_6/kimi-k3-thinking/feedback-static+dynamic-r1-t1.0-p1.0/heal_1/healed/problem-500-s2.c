#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static size_t bounded_strlen(const char *s, size_t max_length)
{
    size_t length = 0;

    while (length < max_length && s[length] != '\0') {
        length++;
    }

    return length;
}

char *concatenate_strings(const char *const *list, size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t i;
    char *result;
    size_t *lengths = NULL;

    if (list == NULL) {
        return NULL;
    }

    if (count > 0) {
        lengths = calloc(count, sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            free(lengths);
            return NULL;
        }

        lengths[i] = bounded_strlen(list[i], MAX_STRING_LENGTH);
        if (lengths[i] == MAX_STRING_LENGTH) {
            free(lengths);
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - total_length - 1) {
            free(lengths);
            return NULL;
        }
        total_length += lengths[i];
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (lengths[i] == 0) {
            continue;
        }

        if (lengths[i] > total_length - offset) {
            free(result);
            free(lengths);
            return NULL;
        }

        memcpy(result + offset, list[i], lengths[i]);
        offset += lengths[i];
    }
    result[offset] = '\0';

    free(lengths);
    return result;
}

int main(void)
{
    const char *list[] = {"Hello", ", ", "world", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);
    char *result = concatenate_strings(list, count);

    if (result == NULL) {
        fprintf(stderr, "Error: failed to concatenate strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}