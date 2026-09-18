#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

float *convert_to_floats(const char *const *string_list, size_t list_size, size_t *out_count);

float *convert_to_floats(const char *const *string_list, size_t list_size, size_t *out_count) {
    if (!out_count) {
        return NULL;
    }

    *out_count = 0;

    if (!string_list || list_size == 0) {
        return NULL;
    }

    float *float_array = malloc(list_size * sizeof(float));
    if (!float_array) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; ++i) {
        if (!string_list[i]) {
            continue;
        }

        char *endptr = NULL;
        errno = 0;
        float val = strtof(string_list[i], &endptr);

        if (endptr == string_list[i]) {
            continue;
        }

        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }

        if (*endptr != '\0') {
            continue;
        }

        if (errno == ERANGE) {
            continue;
        }

        float_array[count++] = val;
    }

    if (count == 0) {
        free(float_array);
        return NULL;
    }

    float *resized_array = realloc(float_array, count * sizeof(float));
    if (!resized_array) {
        *out_count = count;
        return float_array;
    }

    *out_count = count;
    return resized_array;
}

int main(void) {
    const char *const input_list[] = {
        "3.14",
        "invalid",
        "  -2.718  ",
        "1e99", 
        NULL,
        "42",
        "100.5abc",
        "0.0"
    };
    
    size_t list_size = sizeof(input_list) / sizeof(input_list[0]);
    size_t valid_count = 0;

    float *result = convert_to_floats(input_list, list_size, &valid_count);

    if (result) {
        for (size_t i = 0; i < valid_count; ++i) {
            printf("%f\n", result[i]);
        }
        free(result);
    }

    return 0;
}