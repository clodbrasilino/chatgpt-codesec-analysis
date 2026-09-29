#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long integer_part;
    unsigned long long fractional_part;
} NumberTuple;

static bool tuple_to_double(NumberTuple tuple, double *result)
{
    char *buffer;
    char *end;
    double value;
    int length;
    int written;
    size_t buffer_size;

    if (result == NULL) {
        return false;
    }

    length = snprintf(NULL, 0, "%lld.%llu",
                      tuple.integer_part, tuple.fractional_part);
    if (length < 0) {
        return false;
    }

    if ((uintmax_t)length >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    buffer_size = (size_t)length + 1U;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return false;
    }

    written = snprintf(buffer, buffer_size, "%lld.%llu",
                       tuple.integer_part, tuple.fractional_part);
    if (written < 0 || written != length) {
        free(buffer);
        return false;
    }

    errno = 0;
    value = strtod(buffer, &end);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        free(buffer);
        return false;
    }

    free(buffer);
    *result = value;
    return true;
}

int main(void)
{
    const NumberTuple tuple = {4, 56};
    double value;

    if (!tuple_to_double(tuple, &value)) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.2f\n", value);
    return EXIT_SUCCESS;
}