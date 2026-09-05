#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int convert_to_floats(const char * const *list, size_t size, float *out) {
    if (list == NULL || out == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (list[i] == NULL) {
            return -1;
        }

        if (list[i][0] == '\0') {
            out[i] = 0.0f;
            continue;
        }

        char *endptr = NULL;
        errno = 0;
        float val = strtof(list[i], &endptr);

        if (errno == ERANGE) {
            out[i] = 0.0f;
            errno = 0;
        } else if (endptr == list[i]) {
            out[i] = 0.0f;
        } else {
            out[i] = val;
        }
    }

    return 0;
}

int main(void) {
    const char *list[] = {
        "3.14",
        "-42.5",
        "0",
        "1e-3",
        "INF",
        "not_a_float",
        "123abc",
        "",
        "1.7976931348623158e+308"
    };

    size_t size = sizeof(list) / sizeof(list[0]);
    float *out = (float *)malloc(size * sizeof(float));

    if (out == NULL) {
        return EXIT_FAILURE;
    }

    if (convert_to_floats(list, size, out) == 0) {
        for (size_t i = 0; i < size; ++i) {
            printf("Input: '%s' -> Output: %f\n", list[i], out[i]);
        }
    }

    free(out);
    out = NULL;

    return EXIT_SUCCESS;
}