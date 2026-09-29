#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    float *array;
    size_t size;
} FloatArray;

FloatArray convert_to_floats(const char **list, size_t list_size) {
    FloatArray result;
    result.array = NULL;
    result.size = 0;

    if (list == NULL || list_size == 0) {
        return result;
    }

    result.array = (float *)malloc(list_size * sizeof(float));
    if (result.array == NULL) {
        return result;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (list[i] == NULL) {
            continue;
        }

        char *endptr;
        float val = strtof(list[i], &endptr);

        if (endptr != list[i] && *endptr == '\0') {
            result.array[result.size++] = val;
        }
    }

    if (result.size == 0) {
        free(result.array);
        result.array = NULL;
    } else if (result.size < list_size) {
        float *temp = (float *)realloc(result.array, result.size * sizeof(float));
        if (temp != NULL) {
            result.array = temp;
        }
    }

    return result;
}

int main(void) {
    const char *input_list[] = {
        "123.45",
        "abc",
        "67.89",
        "invalid",
        "-42.0",
        NULL,
        "0.001"
    };
    size_t list_size = sizeof(input_list) / sizeof(input_list[0]);

    FloatArray converted = convert_to_floats(input_list, list_size);

    for (size_t i = 0; i < converted.size; ++i) {
        printf("%f\n", converted.array[i]);
    }

    if (converted.array != NULL) {
        free(converted.array);
    }

    return 0;
}