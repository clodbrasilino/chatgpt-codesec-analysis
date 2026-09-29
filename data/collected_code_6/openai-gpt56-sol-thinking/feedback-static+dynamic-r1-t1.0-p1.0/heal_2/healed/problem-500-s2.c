#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_elements(const char *const elements[], size_t count)
{
    size_t *lengths = NULL;
    size_t total_length = 0;
    size_t offset = 0;
    char *result;

    if (count > 0 && elements == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*lengths)) {
        return NULL;
    }

    if (count > 0) {
        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }

        lengths[i] = strlen(elements[i]);

        if (lengths[i] > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }

        total_length += lengths[i];
    }

    if (count > 1) {
        size_t separator_count = count - 1;

        if (separator_count > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }

        total_length += separator_count;
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            result[offset++] = ' ';
        }

        memcpy(result + offset, elements[i], lengths[i]);
        offset += lengths[i];
    }

    result[offset] = '\0';
    free(lengths);

    return result;
}

int main(void)
{
    const char *elements[] = {
        "", "", "hello", "there", "have", "a", "rocky", "day"
    };
    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate_elements(elements, count);

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