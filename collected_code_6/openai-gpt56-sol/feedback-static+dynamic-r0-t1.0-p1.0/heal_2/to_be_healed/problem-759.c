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

    if (text == NULL) {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '\0') {
        return false;
    }

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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t length = 0;
    int ch;
    bool too_long = false;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 < sizeof input) {
            input[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0 && !too_long) {
        return 0;
    }

    input[length] = '\0';

    if (too_long) {
        puts("Invalid");
        return 0;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}