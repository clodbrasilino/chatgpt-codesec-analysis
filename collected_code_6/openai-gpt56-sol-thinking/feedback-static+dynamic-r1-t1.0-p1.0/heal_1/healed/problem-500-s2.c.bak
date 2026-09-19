#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_elements(const char *const elements[], size_t count)
{
    const char prefix[] = "  ";
    const size_t prefix_length = sizeof(prefix) - 1U;
    size_t total_length = prefix_length;
    size_t offset = 0;
    char *result;

    if (count > 0U && elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length;

        if (elements[i] == NULL) {
            return NULL;
        }

        length = strlen(elements[i]);

        if (i > 0U) {
            if (total_length == SIZE_MAX) {
                return NULL;
            }
            ++total_length;
        }

        if (length > SIZE_MAX - total_length) {
            return NULL;
        }

        total_length += length;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, prefix, prefix_length);
    offset = prefix_length;

    for (size_t i = 0; i < count; ++i) {
        size_t length = strlen(elements[i]);

        if (i > 0U) {
            result[offset++] = ' ';
        }

        memcpy(result + offset, elements[i], length);
        offset += length;
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    const char *elements[] = {
        "hello",
        "there",
        "have",
        "a",
        "rocky",
        "day"
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