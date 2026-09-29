#include <stdbool.h>
#include <stdio.h>

static bool is_digit(unsigned char ch)
{
    return ch >= (unsigned char)'0' && ch <= (unsigned char)'9';
}

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == (unsigned char)'+' || *p == (unsigned char)'-') {
        ++p;
    }

    while (is_digit(*p)) {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != (unsigned char)'.') {
        return false;
    }

    ++p;

    if (!is_digit(*p)) {
        return false;
    }

    ++p;

    if (!is_digit(*p)) {
        return false;
    }

    ++p;

    return *p == '\0';
}

static bool discard_line_remainder(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return !ferror(stdin);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t length = 0;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        if (!discard_line_remainder()) {
            return 1;
        }

        puts("Invalid");
        return 0;
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[length - 1] = '\0';
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}