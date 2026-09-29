#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ROMAN_BUFFER_SIZE 32
#define INPUT_BUFFER_SIZE 64
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    static const int values[] = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    static const char symbols[][3] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    static const size_t symbol_lengths[] = {
        1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
    };
    size_t used = 0;
    size_t i;
    size_t j;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (number < MIN_ROMAN_VALUE || number > MAX_ROMAN_VALUE) {
        return -1;
    }

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        while (number >= values[i]) {
            size_t sym_len = symbol_lengths[i];

            if (used >= buffer_size - 1 || sym_len > buffer_size - 1 - used) {
                buffer[0] = '\0';
                return -1;
            }

            for (j = 0; j < sym_len; j++) {
                buffer[used + j] = symbols[i][j];
            }

            used += sym_len;
            buffer[used] = '\0';
            number -= values[i];
        }
    }

    return 0;
}

static int read_int(int *out)
{
    char line[INPUT_BUFFER_SIZE];
    char *endptr;
    long value;

    if (out == NULL) {
        return -1;
    }

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }

    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }

    errno = 0;
    value = strtol(line, &endptr, 10);

    if (endptr == line) {
        return -1;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        return -1;
    }

    if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        return -1;
    }

    *out = (int)value;
    return 0;
}

int main(void)
{
    char roman[ROMAN_BUFFER_SIZE] = { 0 };
    int test_values[] = { 1, 4, 9, 14, 40, 90, 400, 1994, 2024, 3999 };
    size_t i;
    int input;

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        if (int_to_roman(test_values[i], roman, sizeof(roman)) == 0) {
            printf("%d -> %s\n", test_values[i], roman);
        } else {
            fprintf(stderr, "Conversion failed for %d\n", test_values[i]);
            return EXIT_FAILURE;
        }
    }

    printf("Enter an integer (1-3999): ");
    fflush(stdout);

    if (read_int(&input) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (int_to_roman(input, roman, sizeof(roman)) != 0) {
        fprintf(stderr, "Value out of range (1-3999)\n");
        return EXIT_FAILURE;
    }

    printf("%d -> %s\n", input, roman);

    return EXIT_SUCCESS;
}