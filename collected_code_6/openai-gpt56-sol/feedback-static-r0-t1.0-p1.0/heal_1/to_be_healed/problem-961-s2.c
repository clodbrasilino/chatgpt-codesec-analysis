#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

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

static int roman_to_int(const char *roman, int *result)
{
    size_t length;
    long total = 0;
    int previous = 0;
    unsigned int repeat_count = 0;
    char last = '\0';

    if (roman == NULL || result == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(roman);
    if (length == 0U) {
        return 0;
    }

    for (size_t i = length; i > 0U; --i) {
        char current_char = roman[i - 1U];
        int current;

        if (islower((unsigned char)current_char)) {
            current_char = (char)toupper((unsigned char)current_char);
        }

        current = roman_value(current_char);
        if (current == 0) {
            return 0;
        }

        if (current_char == last) {
            ++repeat_count;
        } else {
            last = current_char;
            repeat_count = 1U;
        }

        if ((current_char == 'V' || current_char == 'L' || current_char == 'D') &&
            repeat_count > 1U) {
            return 0;
        }

        if (repeat_count > 3U) {
            return 0;
        }

        if (current < previous) {
            if (!((current == 1 && (previous == 5 || previous == 10)) ||
                  (current == 10 && (previous == 50 || previous == 100)) ||
                  (current == 100 && (previous == 500 || previous == 1000)))) {
                return 0;
            }
            total -= current;
        } else {
            total += current;
            previous = current;
        }

        if (total > INT_MAX || total < INT_MIN) {
            return 0;
        }
    }

    if (total <= 0 || total > 3999) {
        return 0;
    }

    *result = (int)total;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!roman_to_int(argv[1], &value)) {
        fprintf(stderr, "Invalid Roman numeral\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", value);
    return EXIT_SUCCESS;
}