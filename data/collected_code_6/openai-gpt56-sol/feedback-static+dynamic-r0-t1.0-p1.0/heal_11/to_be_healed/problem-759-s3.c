#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_decimal_with_precision_2(const char *text)
{
    if (text == NULL || *text == '\0') {
        return false;
    }

    const unsigned char *p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    while (isdigit(*p)) {
        ++p;
    }

    if (*p != '.') {
        return false;
    }
    ++p;

    if (!isdigit(*p)) {
        return false;
    }
    ++p;

    if (!isdigit(*p)) {
        return false;
    }
    ++p;

    return *p == '\0';
}

int main(void)
{
    enum { INPUT_SIZE = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    bool valid = is_decimal_with_precision_2(input);
    puts(valid ? "Valid" : "Invalid");

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}