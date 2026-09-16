#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int roman_value(char c)
{
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

static int is_valid_subtractive_pair(char first, char second)
{
    return (first == 'I' && (second == 'V' || second == 'X')) ||
           (first == 'X' && (second == 'L' || second == 'C')) ||
           (first == 'C' && (second == 'D' || second == 'M'));
}

static int roman_to_integer(const char *roman, int *result)
{
    size_t i;
    long total = 0;
    char previous = '\0';
    unsigned int repetitions = 0;

    if (roman == NULL || result == NULL || roman[0] == '\0') {
        return 0;
    }

    for (i = 0; roman[i] != '\0'; ++i) {
        int current = roman_value(roman[i]);
        int next = roman_value(roman[i + 1]);

        if (current == 0) {
            return 0;
        }

        if (roman[i] == previous) {
            ++repetitions;
        } else {
            previous = roman[i];
            repetitions = 1;
        }

        if ((roman[i] == 'V' || roman[i] == 'L' || roman[i] == 'D') &&
            repetitions > 1) {
            return 0;
        }

        if (repetitions > 3) {
            return 0;
        }

        if (next > current) {
            if (repetitions != 1 ||
                !is_valid_subtractive_pair(roman[i], roman[i + 1])) {
                return 0;
            }

            total += next - current;
            ++i;
            previous = '\0';
            repetitions = 0;
        } else {
            total += current;
        }

        if (total > INT_MAX) {
            return 0;
        }
    }

    *result = (int)total;
    return 1;
}

int main(int argc, char *argv[])
{
    int value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!roman_to_integer(argv[1], &value)) {
        fprintf(stderr, "Invalid Roman numeral\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", value);
    return EXIT_SUCCESS;
}