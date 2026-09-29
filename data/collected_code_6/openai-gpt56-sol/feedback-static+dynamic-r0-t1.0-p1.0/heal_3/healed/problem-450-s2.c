#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char *const *values, size_t count,
                       size_t start, size_t length)
{
    char **result;
    size_t i;

    if (values == NULL || start > count || length > count - start) {
        return NULL;
    }

    if (length == SIZE_MAX ||
        length + 1 > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = calloc(length + 1, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        const char *source = values[start + i];
        char *copy;

        if (source == NULL) {
            goto failure;
        }

        copy = strdup(source);
        if (copy == NULL) {
            goto failure;
        }

        result[i] = copy;
    }

    return result;

failure:
    while (i > 0) {
        free(result[--i]);
    }

    free(result);
    return NULL;
}

void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

int main(void)
{
    const char *values[] = {
        "alpha",
        "beta",
        "gamma",
        "delta",
        "epsilon"
    };
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t start = 1;
    const size_t length = 3;
    char **extracted;
    size_t i;

    extracted = extract_strings(values, value_count, start, length);
    if (extracted == NULL) {
        fputs("Failed to extract strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (puts(extracted[i]) == EOF) {
            free_strings(extracted, length);
            return EXIT_FAILURE;
        }
    }

    free_strings(extracted, length);
    return EXIT_SUCCESS;
}