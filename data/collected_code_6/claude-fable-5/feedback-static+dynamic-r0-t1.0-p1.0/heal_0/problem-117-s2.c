#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

typedef struct {
    float value;
    int converted;
} FloatResult;

static int is_blank(const char *s)
{
    while (*s != '\0') {
        if (!isspace((unsigned char)*s)) {
            return 0;
        }
        s++;
    }
    return 1;
}

int try_convert_to_float(const char *input, float *out)
{
    char *endptr = NULL;
    float result;

    if (input == NULL || out == NULL) {
        return 0;
    }

    if (is_blank(input)) {
        return 0;
    }

    errno = 0;
    result = strtof(input, &endptr);

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

    if (isnan(result)) {
        return 0;
    }

    *out = result;
    return 1;
}

FloatResult *convert_list_to_floats(const char *const *list, size_t count)
{
    FloatResult *results;
    size_t i;

    if (list == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(FloatResult)) {
        return NULL;
    }

    results = malloc(count * sizeof(FloatResult));
    if (results == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        results[i].value = 0.0f;
        results[i].converted = 0;
        if (list[i] != NULL) {
            float value;
            if (try_convert_to_float(list[i], &value)) {
                results[i].value = value;
                results[i].converted = 1;
            }
        }
    }

    return results;
}

int main(void)
{
    const char *const items[] = {
        "3.14",
        "hello",
        "-42.5",
        "1e3",
        "",
        "  7.25  ",
        "12abc",
        NULL,
        "0.001"
    };
    size_t count = sizeof(items) / sizeof(items[0]);
    FloatResult *results;
    size_t i;

    results = convert_list_to_floats(items, count);
    if (results == NULL) {
        fprintf(stderr, "Conversion failed: could not allocate results\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        const char *original = (items[i] != NULL) ? items[i] : "(null)";
        if (results[i].converted) {
            if (printf("\"%s\" -> %f\n", original, (double)results[i].value) < 0) {
                free(results);
                return EXIT_FAILURE;
            }
        } else {
            if (printf("\"%s\" -> not convertible\n", original) < 0) {
                free(results);
                return EXIT_FAILURE;
            }
        }
    }

    free(results);
    return EXIT_SUCCESS;
}