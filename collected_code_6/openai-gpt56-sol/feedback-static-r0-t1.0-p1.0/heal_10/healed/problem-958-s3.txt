#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INITIAL_CAPACITY = 32,
    MAX_LINE_LENGTH = 4096
};

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
    char *result;
    size_t position = 0U;
    size_t i;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    result = malloc(16U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= 15U) {
                    free(result);
                    return NULL;
                }

                result[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0U;
    size_t capacity = INITIAL_CAPACITY;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character;

        if (length >= MAX_LINE_LENGTH) {
            character = fgetc(stream);
            if (character != '\n' && character != EOF) {
                do {
                    character = fgetc(stream);
                } while (character != '\n' && character != EOF);
            }
            free(buffer);
            return NULL;
        }

        character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            if (new_capacity > (size_t)MAX_LINE_LENGTH + 1U) {
                new_capacity = (size_t)MAX_LINE_LENGTH + 1U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
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