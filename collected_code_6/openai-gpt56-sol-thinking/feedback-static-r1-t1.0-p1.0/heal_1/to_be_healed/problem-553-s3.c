#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long integer_part;
    unsigned long long fractional_part;
} NumberTuple;

static bool tuple_to_double(NumberTuple tuple, double *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end = NULL;
    int length;

    if (result == NULL) {
        return false;
    }

    length = snprintf(buffer, sizeof(buffer), "%lld.%llu",
                      tuple.integer_part, tuple.fractional_part);
    if (length < 0 || (size_t)length >= sizeof(buffer)) {
        return false;
    }

    errno = 0;
    *result = strtod(buffer, &end);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        return false;
    }

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