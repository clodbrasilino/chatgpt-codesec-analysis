#include <stdbool.h>
#include <stddef.h>
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
    if (context == NULL || result == NULL) {
        return false;
    }

    return checked_power(*(const uint64_t *)context, index, result);
}

static bool map_values(uint64_t *output, size_t count, MapFunction function,
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

bool create_power_list(uint64_t base, size_t count, uint64_t **list)
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

    if (!map_values(values, count, power_mapper, &base)) {
        free(values);
        return false;
    }

    *list = values;
    return true;
}

static bool parse_uint64(const char *text, uint64_t *value)
{
    uint64_t parsed = 0;

    if (text == NULL || value == NULL || *text == '\0') {
        return false;
    }

    for (const char *cursor = text; *cursor != '\0'; ++cursor) {
        uint64_t digit;

        if (*cursor < '0' || *cursor > '9') {
            return false;
        }

        digit = (uint64_t)(*cursor - '0');

        if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        parsed = parsed * UINT64_C(10) + digit;
    }

    *value = parsed;
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !parse_uint64(text, &parsed)) {
        return false;
    }

#if SIZE_MAX < UINT64_MAX
    if (parsed > (uint64_t)SIZE_MAX) {
        return false;
    }
#endif

    *value = (size_t)parsed;
    return true;
}

static bool write_uint64(FILE *stream, uint64_t value)
{
    if (stream == NULL) {
        return false;
    }

    if (value >= UINT64_C(10) &&
        !write_uint64(stream, value / UINT64_C(10))) {
        return false;
    }

    return fputc('0' + (int)(value % UINT64_C(10)), stream) != EOF;
}

static void write_usage(const char *program)
{
    if (program == NULL) {
        program = "power-list";
    }

    fputs("Usage: ", stderr);
    fputs(program, stderr);
    fputs(" <base> <count>\n", stderr);
}

int main(int argc, char **argv)
{
    uint64_t base;
    size_t count;
    uint64_t *powers = NULL;

    if (argc != 3 || argv == NULL) {
        write_usage(argv != NULL && argc > 0 ? argv[0] : NULL);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &base) || !parse_size(argv[2], &count)) {
        fputs("Invalid base or count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!create_power_list(base, count, &powers)) {
        fputs("Unable to create the power list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputc('[', stdout) == EOF) {
        free(powers);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (index != 0 && fputs(", ", stdout) == EOF) {
            free(powers);
            return EXIT_FAILURE;
        }

        if (!write_uint64(stdout, powers[index])) {
            free(powers);
            return EXIT_FAILURE;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        free(powers);
        return EXIT_FAILURE;
    }

    free(powers);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}