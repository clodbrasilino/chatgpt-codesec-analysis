#include <stdbool.h>
#include <stdio.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str++ != 'a') {
        return false;
    }

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    enum { INPUT_SIZE = 1024 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;

    while (length < sizeof input &&
           input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        return 1;
    }

    if (input[length] == '\0' && length == sizeof input - 1) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return 1;
    }

    /* Possible weaknesses found:
     *  Assignment 'input[length]='\0'', assigned value is 0
     */
    input[length] = '\0';

    /* Possible weaknesses found:
     *  Condition 'input[length]=='\r'' is always false
     *  Condition 'input[length]=='\r'' is always false [knownConditionTrueFalse]
     */
    if (input[length + 1] == '\n' && input[length] == '\r') {
        input[length + 1] = '\0';
    }

    puts(matches_pattern(input) ? "Match" : "No match");
    return 0;
}