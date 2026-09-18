#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

float* convert_to_floats(const char * const *list, size_t size, size_t *out_size) {
    if (!list || !out_size) {
        return NULL;
    }

    *out_size = 0;

    if (size == 0) {
        return NULL;
    }

    float *results = malloc(size * sizeof(float));
    if (!results) {
        return NULL;
    }

    size_t valid_count = 0;

    for (size_t i = 0; i < size; i++) {
        if (!list[i]) {
            continue;
        }

        char *endptr;
        errno = 0;
        float value = strtof(list[i], &endptr);

        if (list[i] == endptr) {
            continue;
        }

        if (errno == ERANGE) {
            continue;
        }

        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }

        if (*endptr != '\0') {
            continue;
        }

        results[valid_count++] = value;
    }

    *out_size = valid_count;

    if (valid_count == 0) {
        free(results);
        return NULL;
    }

    float *shrunk_results = realloc(results, valid_count * sizeof(float));
    if (!shrunk_results) {
        return results;
    }

    return shrunk_results;
}

int main(void) {
    const char *input_list[] = {
        "3.14",
        "invalid",
        "  -42.5  ",
        "2.71828",
        NULL,
        "1e-4",
        "123abc"
    };
    
    size_t input_size = sizeof(input_list) / sizeof(input_list[0]);
    size_t output_size = 0;

    float *converted = convert_to_floats(input_list, input_size, &output_size);

    if (converted) {
        for (size_t i = 0; i < output_size; i++) {
            printf("%f\n", converted[i]);
        }
        free(converted);
    }

    return 0;
}