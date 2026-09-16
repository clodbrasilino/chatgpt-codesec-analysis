#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {
    float value;
    bool converted;
} FloatResult;

FloatResult *convert_to_floats(const char * const *list, size_t count) {
    if (list == NULL || count == 0) {
        return NULL;
    }

    FloatResult *results = (FloatResult *)malloc(count * sizeof(FloatResult));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL || list[i][0] == '\0') {
            results[i].value = 0.0f;
            results[i].converted = false;
            continue;
        }

        char *endptr = NULL;
        errno = 0;
        float val = strtof(list[i], &endptr);

        if (errno == ERANGE) {
            results[i].value = 0.0f;
            results[i].converted = false;
        } else if (endptr == list[i]) {
            results[i].value = 0.0f;
            results[i].converted = false;
        } else if (*endptr != '\0') {
            results[i].value = 0.0f;
            results[i].converted = false;
        } else {
            results[i].value = val;
            results[i].converted = true;
        }
    }

    return results;
}

int main(void) {
    const char *list[] = {
        "3.14",
        "42",
        "-2.718",
        "hello",
        "1e5",
        "",
        "3.14abc",
        "0",
        "INF",
        "-inf",
        "NAN",
        "9999999999999999999999999999999999999999999999999999e9999",
        NULL
    };

    size_t count = sizeof(list) / sizeof(list[0]);

    FloatResult *results = convert_to_floats(list, count);
    if (results == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL) {
            printf("[%zu] (null) -> NOT CONVERTIBLE\n", i);
        } else if (results[i].converted) {
            printf("[%zu] \"%s\" -> %g\n", i, list[i], results[i].value);
        } else {
            printf("[%zu] \"%s\" -> NOT CONVERTIBLE\n", i, list[i]);
        }
    }

    free(results);
    results = NULL;

    return EXIT_SUCCESS;
}