#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;
    size_t integer_digits = 0;

    if (p == NULL || *p == '\0') {
        return false;
    }

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
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == sizeof input - 1) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin) != 0) {
            return 1;
        }

        puts("Invalid");
        return 0;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}