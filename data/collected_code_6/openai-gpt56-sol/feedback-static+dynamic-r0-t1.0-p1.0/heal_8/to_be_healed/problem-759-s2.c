#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

static bool is_decimal_with_precision_2(const char *text)
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

    while (*p >= '0' && *p <= '9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    return p[0] >= '0' && p[0] <= '9' &&
           p[1] >= '0' && p[1] <= '9' &&
           p[2] == '\0';
}

static bool read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    length = 0;
    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (length == capacity || buffer[length] != '\0') {
        return false;
    }

    if (feof(stdin)) {
        return true;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == '\n') {
            return true;
        }

        while (character != '\n' && character != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    if (!read_line(input, sizeof input)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}