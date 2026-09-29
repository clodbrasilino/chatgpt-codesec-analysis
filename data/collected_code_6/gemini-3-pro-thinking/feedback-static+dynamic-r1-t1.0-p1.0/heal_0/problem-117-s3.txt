#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

float* convert_to_floats(const char *const *list, size_t count, size_t *out_count) {
    if (list == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (count == 0) {
        return NULL;
    }

    float *results = malloc(count * sizeof(float));
    if (results == NULL) {
        return NULL;
    }

    size_t valid_count = 0;

    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }

        const char *str = list[i];
        while (isspace((unsigned char)*str)) {
            str++;
        }

        if (*str == '\0') {
            continue;
        }

        char *endptr = NULL;
        errno = 0;
        float value = strtof(str, &endptr);

        if (str == endptr) {
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

        results[valid_count] = value;
        valid_count++;
    }

    *out_count = valid_count;

    if (valid_count == 0) {
        free(results);
        return NULL;
    }

    if (valid_count < count) {
        float *resized = realloc(results, valid_count * sizeof(float));
        if (resized != NULL) {
            results = resized;
        }
    }

    return results;
}

int main(void) {
    const char *const string_list[] = {
        "3.14159",
        "  -42.5  ",
        "invalid_string",
        "1e39", 
        "100.0x",
        NULL,
        "0.0"
    };
    
    size_t list_size = sizeof(string_list) / sizeof(string_list[0]);
    size_t converted_count = 0;

    float *converted_floats = convert_to_floats(string_list, list_size, &converted_count);

    if (converted_floats != NULL) {
        for (size_t i = 0; i < converted_count; i++) {
            printf("%f\n", converted_floats[i]);
        }
        free(converted_floats);
    }

    return 0;
}