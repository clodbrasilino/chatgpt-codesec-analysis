#include <errno.h>
#include <inttypes.h>
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
    if (context == NULL) {
        return false;
    }

    return checked_power(*(const uint64_t *)context, index, result);
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

    if (text == NULL || value == NULL || text[0] == '\0') {
        return false;
    }

    for (const char *cursor = text; *cursor != '\0'; ++cursor) {
        if (*cursor < '0' || *cursor > '9') {
            return false;
        }
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)parsed;
    return true;
}

static bool parse_size(const char *text, size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !parse_uint64(text, &parsed) || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    uint64_t base;
    size_t count;
    uint64_t *powers = NULL;

    if (argc != 3) {
        const char *program =
            argc > 0 && argv[0] != NULL ? argv[0] : "power-list";

        fprintf(stderr, "Usage: %s <base> <count>\n", program);
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

        /* Possible weaknesses found:
         * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        if (printf("%" PRIu64, powers[index]) < 0) {
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