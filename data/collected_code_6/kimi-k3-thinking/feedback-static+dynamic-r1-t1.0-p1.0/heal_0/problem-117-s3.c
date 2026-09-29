#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

size_t convert_to_float(const char *const *list, size_t count, float *results, bool *converted)
{
    size_t success = 0;
    size_t i;

    if (list == NULL || results == NULL || converted == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        char *endptr = NULL;
        float value = 0.0f;

        results[i] = 0.0f;
        converted[i] = false;

        if (list[i] == NULL) {
            continue;
        }

        errno = 0;
        value = strtof(list[i], &endptr);

        if (endptr == list[i]) {
            continue;
        }

        while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
            endptr++;
        }

        if (*endptr != '\0') {
            continue;
        }

        if (errno == ERANGE && (value == HUGE_VALF || value == -HUGE_VALF)) {
            continue;
        }

        results[i] = value;
        converted[i] = true;
        success++;
    }

    return success;
}

int main(void)
{
    const char *list[] = {
        "3.14", "-2.5", "42", "hello", "1e3",
        "0.75", "", "12abc", "  8.5  ", "1e999"
    };
    const size_t count = sizeof(list) / sizeof(list[0]);
    float *results = NULL;
    bool *converted = NULL;
    size_t converted_count = 0;
    size_t i = 0;

    results = malloc(count * sizeof(*results));
    if (results == NULL) {
        fprintf(stderr, "Failed to allocate memory for results\n");
        return EXIT_FAILURE;
    }

    converted = malloc(count * sizeof(*converted));
    if (converted == NULL) {
        fprintf(stderr, "Failed to allocate memory for conversion flags\n");
        free(results);
        results = NULL;
        return EXIT_FAILURE;
    }

    converted_count = convert_to_float(list, count, results, converted);

    printf("Converted %zu out of %zu elements:\n", converted_count, count);
    for (i = 0; i < count; i++) {
        if (converted[i]) {
            printf("[%zu] \"%s\" -> %f\n", i, list[i], (double)results[i]);
        } else {
            printf("[%zu] \"%s\" -> not convertible\n", i, list[i]);
        }
    }

    free(converted);
    converted = NULL;
    free(results);
    results = NULL;

    return EXIT_SUCCESS;
}