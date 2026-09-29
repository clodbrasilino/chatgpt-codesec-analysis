#include <ctype.h>
#include <stdio.h>

#define INPUT_CAPACITY 4096U

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned int digit;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'begin<end' is not redundant
     */
    while (begin < end && isspace((unsigned char)hex[end - 1U])) {
        --end;
    }

    /* Possible weaknesses found:
     *  Condition 'end-begin>=2U' is always false
     *  Condition 'end-begin>=2U' is always false [knownConditionTrueFalse]
     */
    if (end - begin >= 2U &&
        hex[begin] == '0' &&
        (hex[begin + 1U] == 'x' || hex[begin + 1U] == 'X')) {
        begin += 2U;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    digit = (unsigned int)(unsigned char)hex[end - 1U];

    if (digit >= (unsigned int)'0' && digit <= (unsigned int)'9') {
        digit -= (unsigned int)'0';
    } else {
        digit = (unsigned int)tolower((unsigned char)digit)
              - (unsigned int)'a' + 10U;
    }

    *is_even = (digit % 2U) == 0U;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY + 1U];
    size_t length = 0U;
    int is_even = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        return 1;
    }

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Invalid hexadecimal number\n", stderr);
            }
            return 1;
        }

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return 1;
        }
    }

    if (!is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_even ? "Even" : "Odd");
    return 0;
}