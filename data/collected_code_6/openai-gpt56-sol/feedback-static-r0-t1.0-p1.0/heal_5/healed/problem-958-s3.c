#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        const char *symbol;
    } numerals[] = {
        {1000U, "M"},
        {900U, "CM"},
        {500U, "D"},
        {400U, "CD"},
        {100U, "C"},
        {90U, "XC"},
        {50U, "L"},
        {40U, "XL"},
        {10U, "X"},
        {9U, "IX"},
        {5U, "V"},
        {4U, "IV"},
        {1U, "I"}
    };
    size_t length = 0U;
    size_t position = 0U;
    size_t i;
    unsigned int remaining;
    char *result;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    remaining = value;
    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (remaining >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                ++length;
                ++symbol;
            }

            remaining -= numerals[i].value;
        }
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    remaining = value;
    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (remaining >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                result[position++] = *symbol++;
            }

            remaining -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    for (;;) {
        character = fgetc(stream);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && (ferror(stream) || length == 0U)) {
        free(buffer);
        return NULL;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);
        if (buffer == NULL) {
            return NULL;
        }
    } else if (length >= capacity) {
        char *resized = realloc(buffer, length + 1U);

        if (resized == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = resized;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *end;
    char *roman;
    unsigned long parsed;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoul(input, &end, 10);

    if (end == input || *end != '\0' || errno == ERANGE ||
        parsed == 0UL || parsed > 3999UL) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    roman = integer_to_roman((unsigned int)parsed);
    if (roman == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}