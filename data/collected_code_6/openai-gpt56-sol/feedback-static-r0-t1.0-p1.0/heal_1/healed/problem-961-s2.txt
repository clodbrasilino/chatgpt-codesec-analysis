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

static int roman_to_int(const char *roman, int *result)
{
    char normalized[MAX_ROMAN_LENGTH + 1U];
    char canonical[MAX_ROMAN_LENGTH + 1U];
    const char *thousands[] = {"", "M", "MM", "MMM"};
    const char *hundreds[] = {
        "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"
    };
    const char *tens[] = {
        "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"
    };
    const char *ones[] = {
        "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
    };
    size_t length = 0U;
    int total = 0;
    int previous = 0;
    int written;

    if (roman == NULL || result == NULL) {
        return 0;
    }

    while (length <= MAX_ROMAN_LENGTH && roman[length] != '\0') {
        normalized[length] = ascii_upper(roman[length]);
        if (roman_value(normalized[length]) == 0) {
            return 0;
        }
        ++length;
    }

    if (length == 0U || length > MAX_ROMAN_LENGTH) {
        return 0;
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
        sizeof(canonical),
        "%s%s%s%s",
        thousands[total / 1000],
        hundreds[(total / 100) % 10],
        tens[(total / 10) % 10],
        ones[total % 10]
    );

    if (written < 0 || (size_t)written >= sizeof(canonical) ||
        strcmp(normalized, canonical) != 0) {
        return 0;
    }

    *result = total;
    return 1;
}

int main(int argc, char *argv[])
{
    int value;
    const char *program_name =
        (argc > 0 && argv != NULL && argv[0] != NULL) ? argv[0] : "roman";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", program_name);
        return EXIT_FAILURE;
    }

    if (!roman_to_int(argv[1], &value)) {
        fprintf(stderr, "Invalid Roman numeral\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", value);
    return EXIT_SUCCESS;
}