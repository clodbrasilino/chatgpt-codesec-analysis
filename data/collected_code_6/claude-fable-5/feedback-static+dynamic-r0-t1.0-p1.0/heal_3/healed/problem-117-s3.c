#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

typedef struct {
    float value;
    int converted;
} FloatResult;

static int is_blank_string(const char *s)
{
    if (s == NULL) {
        return 1;
    }
    while (*s != '\0') {
        if (!isspace((unsigned char)*s)) {
            return 0;
        }
        s++;
    }
    return 1;
}

static int try_convert_to_float(const char *input, float *out)
{
    char *endptr = NULL;
    double parsed;

    if (input == NULL || out == NULL) {
        return 0;
    }

    if (is_blank_string(input)) {
        return 0;
    }

    errno = 0;
    parsed = strtod(input, &endptr);

    if (endptr == input) {
        return 0;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return 0;
        }
        endptr++;
    }

    if (errno == ERANGE) {
        return 0;
    }

    if (!isfinite(parsed)) {
        return 0;
    }

    if (parsed > (double)FLT_MAX || parsed < -(double)FLT_MAX) {
        return 0;
    }

    *out = (float)parsed;
    return 1;
}

static FloatResult *convert_list_to_floats(const char *const *list, size_t count)
{
    FloatResult *results;
    size_t i;

    if (list == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(FloatResult)) {
        return NULL;
    }

    results = calloc(count, sizeof(FloatResult));
    if (results == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        results[i].value = 0.0f;
        results[i].converted = 0;
        if (list[i] != NULL) {
            results[i].converted = try_convert_to_float(list[i], &results[i].value);
        }
    }

    return results;
}

int main(void)
{
    static const char *const list[] = {
        "3.14",
        "hello",
        "42",
        "-0.5",
        "1e3",
        "abc123",
        "  7.25  ",
        ""
    };
    const size_t list_count = sizeof(list) / sizeof(list[0]);
    FloatResult *results;
    size_t i;

    results = convert_list_to_floats(list, list_count);
    if (results == NULL) {
        fprintf(stderr, "Conversion failed: could not allocate results\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; i++) {
        const char *element = (list[i] != NULL) ? list[i] : "(null)";

        if (results[i].converted) {
            if (printf("Element \"%s\" converted to float: %f\n",
                       element, (double)results[i].value) < 0) {
                free(results);
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Element \"%s\" is not convertible to float\n",
                       element) < 0) {
                free(results);
                return EXIT_FAILURE;
            }
        }
    }

    free(results);
    return EXIT_SUCCESS;
}