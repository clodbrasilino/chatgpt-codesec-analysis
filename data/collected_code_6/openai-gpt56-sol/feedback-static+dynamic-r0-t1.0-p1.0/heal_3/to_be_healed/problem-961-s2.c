#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_MAX_LENGTH 15U

static int roman_value(unsigned char c)
{
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:  return 0;
    }
}

static int roman_to_int(const char *roman, int *result)
{
    static const struct {
        int value;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char symbol[3];
        size_t length;
    } symbols[] = {
        {1000, "M",  1U},
        { 900, "CM", 2U},
        { 500, "D",  1U},
        { 400, "CD", 2U},
        { 100, "C",  1U},
        {  90, "XC", 2U},
        {  50, "L",  1U},
        {  40, "XL", 2U},
        {  10, "X",  1U},
        {   9, "IX", 2U},
        {   5, "V",  1U},
        {   4, "IV", 2U},
        {   1, "I",  1U}
    };

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[ROMAN_MAX_LENGTH + 1U];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char canonical[ROMAN_MAX_LENGTH + 1U];
    size_t length = 0U;
    size_t position = 0U;
    int total = 0;
    int remaining;

    if (roman == NULL || result == NULL) {
        return 0;
    }

    while (roman[length] != '\0') {
        unsigned char c;

        if (length >= ROMAN_MAX_LENGTH) {
            return 0;
        }

        c = (unsigned char)roman[length];

        if (c >= (unsigned char)'a' && c <= (unsigned char)'z') {
            c = (unsigned char)(c - (unsigned char)'a' + (unsigned char)'A');
        }

        if (roman_value(c) == 0) {
            return 0;
        }

        normalized[length] = (char)c;
        ++length;
    }

    if (length == 0U) {
        return 0;
    }

    normalized[length] = '\0';

    for (size_t i = 0U; i < length; ++i) {
        int current = roman_value((unsigned char)normalized[i]);
        int next = i + 1U < length
            ? roman_value((unsigned char)normalized[i + 1U])
            : 0;

        total += current < next ? -current : current;
    }

    if (total < 1 || total > 3999) {
        return 0;
    }

    remaining = total;

    for (size_t i = 0U; i < sizeof(symbols) / sizeof(symbols[0]); ++i) {
        while (remaining >= symbols[i].value) {
            if (symbols[i].length > ROMAN_MAX_LENGTH - position) {
                return 0;
            }

            for (size_t j = 0U; j < symbols[i].length; ++j) {
                canonical[position++] = symbols[i].symbol[j];
            }

            remaining -= symbols[i].value;
        }
    }

    canonical[position] = '\0';

    if (remaining != 0 || position != length ||
        memcmp(canonical, normalized, length) != 0) {
        return 0;
    }

    *result = total;
    return 1;
}

int main(int argc, char *argv[])
{
    int value;

    if (argc != 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "roman";

        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", program);
        return EXIT_FAILURE;
    }

    if (argv == NULL || !roman_to_int(argv[1], &value)) {
        fputs("Invalid Roman numeral\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}