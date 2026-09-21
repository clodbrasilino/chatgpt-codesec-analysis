#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    const char *symbol;
    size_t length;
} RomanMapping;

bool integer_to_roman(int value, char **result)
{
    static const RomanMapping mappings[] = {
        {1000, "M", 1},
        {900, "CM", 2},
        {500, "D", 1},
        {400, "CD", 2},
        {100, "C", 1},
        {90, "XC", 2},
        {50, "L", 1},
        {40, "XL", 2},
        {10, "X", 1},
        {9, "IX", 2},
        {5, "V", 1},
        {4, "IV", 2},
        {1, "I", 1}
    };

    const size_t mapping_count = sizeof(mappings) / sizeof(mappings[0]);
    size_t required = 0;
    size_t position = 0;
    int remaining;
    char *buffer;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    if (value < 1 || value > 3999) {
        return false;
    }

    remaining = value;

    for (size_t i = 0; i < mapping_count; ++i) {
        int count = remaining / mappings[i].value;

        required += (size_t)count * mappings[i].length;
        remaining %= mappings[i].value;
    }

    buffer = malloc(required + 1);
    if (buffer == NULL) {
        return false;
    }

    remaining = value;

    for (size_t i = 0; i < mapping_count; ++i) {
        while (remaining >= mappings[i].value) {
            for (size_t j = 0; j < mappings[i].length; ++j) {
                buffer[position++] = mappings[i].symbol[j];
            }

            remaining -= mappings[i].value;
        }
    }

    buffer[position] = '\0';
    *result = buffer;

    return true;
}

int main(int argc, char *argv[])
{
    char *roman = NULL;
    char *end = NULL;
    long value;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "roman";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <integer from 1 to 3999>\n", program_name);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        value < 1 ||
        value > 3999) {
        fprintf(stderr, "Invalid integer: expected a value from 1 to 3999\n");
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, &roman)) {
        fprintf(stderr, "Roman numeral conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}