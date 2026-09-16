#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool parse_float(const char *text, float *value)
{
    char *end = NULL;
    float result;

    if (text == NULL || value == NULL) {
        return false;
    }

    errno = 0;
    result = strtof(text, &end);

    if (end == text || errno != 0) {
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *value = result;
    return true;
}

static bool convert_list_to_floats(const char *const list[],
                                   size_t length,
                                   float values[],
                                   bool converted[],
                                   size_t *converted_count)
{
    size_t i;

    if (converted_count == NULL) {
        return false;
    }

    *converted_count = 0;

    if (length > 0U &&
        (list == NULL || values == NULL || converted == NULL)) {
        return false;
    }

    for (i = 0U; i < length; ++i) {
        values[i] = 0.0F;
        converted[i] = parse_float(list[i], &values[i]);

        if (converted[i]) {
            ++(*converted_count);
        }
    }

    return true;
}

int main(void)
{
    const char *const list[] = {
        "12.5",
        "invalid",
        "-3.75",
        "42",
        "1.2e3",
        "8.5x",
        "  6.25  ",
        NULL
    };
    const size_t length = sizeof(list) / sizeof(list[0]);
    float values[sizeof(list) / sizeof(list[0])];
    bool converted[sizeof(list) / sizeof(list[0])];
    size_t converted_count;
    size_t i;

    if (!convert_list_to_floats(list, length, values, converted,
                                &converted_count)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; ++i) {
        int result;

        if (converted[i]) {
            result = printf("%s -> %g\n", list[i], (double)values[i]);
        } else {
            result = printf("%s -> not convertible\n",
                            list[i] == NULL ? "(null)" : list[i]);
        }

        if (result < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("Converted: %zu\n", converted_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}