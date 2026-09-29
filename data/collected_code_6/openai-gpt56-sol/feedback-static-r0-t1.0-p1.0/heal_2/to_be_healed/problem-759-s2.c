#include <stdbool.h>
#include <stdio.h>

#define INPUT_SIZE 256

static bool is_decimal_with_precision_2(const char *text)
{
    size_t i = 0;
    size_t integer_digits = 0;

    if (text == NULL || text[0] == '\0') {
        return false;
    }

    if (text[i] == '+' || text[i] == '-') {
        ++i;
    }

    while (text[i] >= '0' && text[i] <= '9') {
        ++integer_digits;
        ++i;
    }

    if (integer_digits == 0 || text[i] != '.') {
        return false;
    }

    ++i;

    if (text[i] < '0' || text[i] > '9') {
        return false;
    }

    ++i;

    if (text[i] < '0' || text[i] > '9') {
        return false;
    }

    ++i;

    return text[i] == '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t length = 0;
    int character;

    while (length + 1 < sizeof input) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (length + 1 == sizeof input) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                return 1;
            }

            fputs("Input too long\n", stderr);
            return 1;
        }
    }

    input[length] = '\0';

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}