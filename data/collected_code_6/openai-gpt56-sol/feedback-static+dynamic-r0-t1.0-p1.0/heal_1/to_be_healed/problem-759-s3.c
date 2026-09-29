#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (isdigit(*p) != 0) {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    if (isdigit(p[0]) == 0 || isdigit(p[1]) == 0) {
        return false;
    }

    return p[2] == '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (is_decimal_with_precision_2(input)) {
        puts("Valid");
        return 0;
    }

    puts("Invalid");
    return 1;
}