#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LEN 64

static int roman_char_value(char c)
{
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default:  return -1;
    }
}

static int roman_to_int(const char *roman, int *result)
{
    size_t len;
    size_t i;
    int total;

    if (roman == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(roman, MAX_ROMAN_LEN + 1);
    if (len == 0 || len > MAX_ROMAN_LEN) {
        return -1;
    }

    total = 0;
    for (i = 0; i < len; i++) {
        int current = roman_char_value(roman[i]);
        if (current < 0) {
            return -1;
        }
        if (i + 1 < len) {
            int next = roman_char_value(roman[i + 1]);
            if (next < 0) {
                return -1;
            }
            if (current < next) {
                total -= current;
            } else {
                total += current;
            }
        } else {
            total += current;
        }
        if (total < 0 || total > 3999999) {
            return -1;
        }
    }

    *result = total;
    return 0;
}

int main(int argc, char const *argv[])
{
    int value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <roman_numeral>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (roman_to_int(argv[1], &value) != 0) {
        fprintf(stderr, "Error: invalid roman numeral '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%s = %d\n", argv[1], value);
    return EXIT_SUCCESS;
}