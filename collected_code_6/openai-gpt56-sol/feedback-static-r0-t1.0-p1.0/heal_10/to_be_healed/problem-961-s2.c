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

static int append_text(
    char *destination,
    size_t capacity,
    size_t *used,
    const char *source,
    size_t source_length)
{
    if (destination == NULL || used == NULL || source == NULL ||
        capacity == 0U || *used >= capacity) {
        return 0;
    }

    if (source_length > capacity - *used - 1U) {
        return 0;
    }

    if (source_length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination + *used, source, source_length);
    }

    *used += source_length;
    destination[*used] = '\0';

    return 1;
}

static int roman_to_int(const char *roman, int *result)
{
    static const char thousands[][4] = {
        "", "M", "MM", "MMM"
    };
    static const char hundreds[][5] = {
        "", "C", "CC", "CCC", "CD",
        "D", "DC", "DCC", "DCCC", "CM"
    };
    static const char tens[][5] = {
        "", "X", "XX", "XXX", "XL",
        "L", "LX", "LXX", "LXXX", "XC"
    };
    static const char ones[][5] = {
        "", "I", "II", "III", "IV",
        "V", "VI", "VII", "VIII", "IX"
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
    size_t used = 0U;
    size_t index;
    size_t group_index;
    size_t group_length;
    int total = 0;
    int previous = 0;

    if (roman == NULL || result == NULL) {
        return 0;
    }

    if (!bounded_length(roman, MAX_ROMAN_LENGTH, &length) || length == 0U) {
        return 0;
    }

    for (index = 0U; index < length; ++index) {
        char current = ascii_upper(roman[index]);

        if (roman_value(current) == 0) {
            return 0;
        }

        normalized[index] = current;
    }
    normalized[length] = '\0';

    for (index = length; index > 0U; --index) {
        int current = roman_value(normalized[index - 1U]);

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

    canonical[0] = '\0';

    group_index = (size_t)total / 1000U;
    group_length = sizeof thousands[group_index] -
                   (sizeof thousands[group_index] -
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    strlen(thousands[group_index]));
    if (!append_text(canonical, sizeof canonical, &used,
                     thousands[group_index], group_length)) {
        return 0;
    }

    group_index = ((size_t)total / 100U) % 10U;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    group_length = strlen(hundreds[group_index]);
    if (!append_text(canonical, sizeof canonical, &used,
                     hundreds[group_index], group_length)) {
        return 0;
    }

    group_index = ((size_t)total / 10U) % 10U;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    group_length = strlen(tens[group_index]);
    if (!append_text(canonical, sizeof canonical, &used,
                     tens[group_index], group_length)) {
        return 0;
    }

    group_index = (size_t)total % 10U;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    group_length = strlen(ones[group_index]);
    if (!append_text(canonical, sizeof canonical, &used,
                     ones[group_index], group_length)) {
        return 0;
    }

    if (length != used || memcmp(normalized, canonical, length) != 0) {
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