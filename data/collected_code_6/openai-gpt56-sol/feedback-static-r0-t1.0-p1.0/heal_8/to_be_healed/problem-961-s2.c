#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 15U

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

static char ascii_upper(char c)
{
    if (c >= 'a' && c <= 'z') {
        return (char)(c - 'a' + 'A');
    }

    return c;
}

static int bounded_length(const char *text, size_t maximum, size_t *length)
{
    size_t i;

    if (text == NULL || length == NULL) {
        return 0;
    }

    for (i = 0U; i <= maximum; ++i) {
        if (text[i] == '\0') {
            *length = i;
            return 1;
        }
    }

    return 0;
}

static int roman_to_int(const char *roman, int *result)
{
    static const char *const thousands[] = {"", "M", "MM", "MMM"};
    static const char *const hundreds[] = {
        "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"
    };
    static const char *const tens[] = {
        "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"
    };
    static const char *const ones[] = {
        "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_ROMAN_LENGTH + 1U];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char canonical[MAX_ROMAN_LENGTH + 1U];
    size_t length;
    int total = 0;
    int previous = 0;
    int written;

    if (roman == NULL || result == NULL) {
        return 0;
    }

    if (!bounded_length(roman, MAX_ROMAN_LENGTH, &length) || length == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        char current = ascii_upper(roman[i]);

        if (roman_value(current) == 0) {
            return 0;
        }

        normalized[i] = current;
    }
    normalized[length] = '\0';

    for (size_t i = length; i > 0U; --i) {
        int current = roman_value(normalized[i - 1U]);

        if (current < previous) {
            total -= current;
        } else {
            total += current;
            previous = current;
        }
    }

    if (total < 1 || total > 3999) {
        return 0;
    }

    written = snprintf(
        canonical,
        sizeof canonical,
        "%s%s%s%s",
        thousands[total / 1000],
        hundreds[(total / 100) % 10],
        tens[(total / 10) % 10],
        ones[total % 10]
    );

    if (written < 0 || (size_t)written >= sizeof canonical) {
        return 0;
    }

    if (strcmp(normalized, canonical) != 0) {
        return 0;
    }

    *result = total;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *program_name = "roman";
    int value;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", program_name);
        return EXIT_FAILURE;
    }

    if (!roman_to_int(argv[1], &value)) {
        fputs("Invalid Roman numeral\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}