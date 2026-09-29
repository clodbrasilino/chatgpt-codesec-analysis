#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    float* values;
    size_t count;
} FloatArray;

int is_convertible_to_float(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    char* endptr;
    strtof(str, &endptr);

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    return *endptr == '\0';
}

FloatArray convert_to_floats(const char** list, size_t list_size) {
    FloatArray result = {NULL, 0};

    if (list == NULL || list_size == 0) {
        return result;
    }

    result.values = (float*)malloc(list_size * sizeof(float));
    if (result.values == NULL) {
        return result;
    }

    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL && is_convertible_to_float(list[i])) {
            result.values[result.count] = strtof(list[i], NULL);
            result.count++;
        }
    }

    if (result.count == 0) {
        free(result.values);
        result.values = NULL;
    } else if (result.count < list_size) {
        float* temp = (float*)realloc(result.values, result.count * sizeof(float));
        if (temp != NULL) {
            result.values = temp;
        }
    }

    return result;
}

int main(void) {
    const char* input_list[] = {
        "3.14",
        "not a float",
        "-42.5",
        "  100.0  ",
        NULL,
        "0",
        "1e3"
    };
    size_t list_size = sizeof(input_list) / sizeof(input_list[0]);

    FloatArray converted = convert_to_floats(input_list, list_size);

    for (size_t i = 0; i < converted.count; i++) {
        printf("%f\n", converted.values[i]);
    }

    if (converted.values != NULL) {
        free(converted.values);
    }

    return 0;
}