#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *concatenate(const char *const elements[],
                  const size_t lengths[],
                  size_t count)
{
    size_t total_length = 0;

    if (count != 0 && (elements == NULL || lengths == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - 1 - total_length) {
            return NULL;
        }

        total_length += lengths[i];
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < lengths[i]; ++j) {
            result[offset++] = elements[i][j];
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    const char *const elements[] = {
        "Hello",
        ", ",
        "world",
        "!"
    };

    const size_t lengths[] = {
        sizeof("Hello") - 1,
        sizeof(", ") - 1,
        sizeof("world") - 1,
        sizeof("!") - 1
    };

    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate(elements, lengths, count);

    if (result == NULL) {
        fputs("Failed to concatenate elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}