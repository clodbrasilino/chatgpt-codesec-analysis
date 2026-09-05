#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int convert_list_to_float(const char * const *list, size_t size, float *out) {
    size_t i;
    char *endptr;
    double val;

    if (list == NULL || out == NULL) {
        return -1;
    }

    for (i = 0; i < size; ++i) {
        if (list[i] == NULL) {
            out[i] = 0.0f;
            continue;
        }

        if (list[i][0] == '\0') {
            out[i] = 0.0f;
            continue;
        }

        errno = 0;
        val = strtod(list[i], &endptr);

        if (errno == ERANGE) {
            out[i] = 0.0f;
            continue;
        }

        if (endptr == list[i]) {
            out[i] = 0.0f;
            continue;
        }

        if (val > 0.0 && val > (double)3.402823466e38f) {
            out[i] = 0.0f;
            continue;
        }

        if (val < 0.0 && val < (double)-3.402823466e38f) {
            out[i] = 0.0f;
            continue;
        }

        if (val != 0.0 && val > -1.175494351e-38f && val < 1.175494351e-38f) {
            out[i] = 0.0f;
            continue;
        }

        out[i] = (float)val;
    }

    return 0;
}

int main(void) {
    const char *list[] = {
        "3.14159",
        "-2.718",
        "1e5",
        "not_a_float",
        "",
        "123.456abc",
        "999999999999999999999999999999999999999999999999999999999999",
        "-999999999999999999999999999999999999999999999999999999999999",
        "1e-50",
        "0"
    };
    size_t size = sizeof(list) / sizeof(list[0]);
    float *out = malloc(size * sizeof(float));

    if (out == NULL) {
        return EXIT_FAILURE;
    }

    if (convert_list_to_float(list, size, out) != 0) {
        free(out);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("list[%zu]: \"%s\" -> %f\n", i, list[i], out[i]);
    }

    free(out);
    return EXIT_SUCCESS;
}