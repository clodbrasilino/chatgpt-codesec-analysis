#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool (*MapFunction)(size_t, const void *, uint64_t *);

static bool checked_power(uint64_t base, size_t exponent, uint64_t *result)
{
    uint64_t value = 1;
    uint64_t factor = base;

    if (result == NULL) {
        return false;
    }

    while (exponent != 0) {
        if ((exponent & 1U) != 0U) {
            if (factor != 0 && value > UINT64_MAX / factor) {
                return false;
            }

            value *= factor;
        }

        exponent >>= 1U;

        if (exponent != 0) {
            if (factor != 0 && factor > UINT64_MAX / factor) {
                return false;
            }

            factor *= factor;
        }
    }

    *result = value;
    return true;
}

static bool power_mapper(size_t index, const void *context, uint64_t *result)
{
    const uint64_t *base = context;

    if (base == NULL || result == NULL) {
        return false;
    }

    return checked_power(*base, index, result);
}

static bool map(uint64_t *output, size_t count, MapFunction function,
                const void *context)
{
    if ((output == NULL && count != 0) || function == NULL) {
        return false;
    }

    for (size_t index = 0; index < count; ++index) {
        if (!function(index, context, &output[index])) {
            return false;
        }
    }

    return true;
}

static bool create_power_list(uint64_t base, size_t count, uint64_t **list)
{
    uint64_t *values;

    if (list == NULL) {
        return false;
    }

    *list = NULL;

    if (count == 0) {
        return true;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return false;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return false;
    }

    if (!map(values, count, power_mapper, &base)) {
        free(values);
        return false;
    }

    *list = values;
    return true;
}

static bool parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL ||
        text[0] < '0' || text[0] > '9') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || end == NULL ||
        *end != '\0' || parsed > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)parsed;
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    uint64_t parsed;

    if (value == NULL ||
        !parse_uint64(text, &parsed) ||
        parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool print_uint64(FILE *stream, uint64_t value)
{
    char buffer[sizeof(value) * CHAR_BIT];
    char *begin = buffer + sizeof(buffer);
    char *position = begin;

    if (stream == NULL) {
        return false;
    }

    do {
        *--position = (char)('0' + value % 10U);
        value /= 10U;
    } while (value != 0);

    return fwrite(position, 1, (size_t)(begin - position), stream) ==
           (size_t)(begin - position);
}

static bool print_power_list(const uint64_t *powers, size_t count)
{
    if (powers == NULL && count != 0) {
        return false;
    }

    if (fputc('[', stdout) == EOF) {
        return false;
    }

    for (size_t index = 0; index < count; ++index) {
        if (index != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (!print_uint64(stdout, powers[index])) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

static void print_usage(const char *program)
{
    if (program == NULL) {
        program = "program";
    }

    fputs("Usage: ", stderr);
    fputs(program, stderr);
    fputs(" <base> <count>\n", stderr);
}

int main(int argc, char *argv[])
{
    uint64_t base;
    size_t count;
    uint64_t *powers = NULL;

    if (argc != 3 || argv == NULL) {
        const char *program = NULL;

        if (argc > 0 && argv != NULL) {
            program = argv[0];
        }

        print_usage(program);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &base) ||
        !parse_size(argv[2], &count)) {
        fputs("Invalid base or count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!create_power_list(base, count, &powers)) {
        fputs("Unable to create the power list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_power_list(powers, count)) {
        free(powers);
        return EXIT_FAILURE;
    }

    free(powers);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}