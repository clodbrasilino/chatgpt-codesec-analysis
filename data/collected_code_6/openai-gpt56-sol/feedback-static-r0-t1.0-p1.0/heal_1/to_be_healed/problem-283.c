#include <stdio.h>
#include <stdlib.h>

static int has_valid_digit_frequencies(const char *text)
{
    size_t frequencies[10] = {0U};

    if (text == NULL || *text == '\0') {
        return 0;
    }

    for (const char *p = text; *p != '\0'; ++p) {
        unsigned char digit;

        if (*p < '0' || *p > '9') {
            return 0;
        }

        digit = (unsigned char)(*p - '0');
        ++frequencies[digit];

        if (frequencies[digit] > digit) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    /* Possible weaknesses found:
     *  Assuming that condition 'input[length]!='\0'' is not redundant
     *  Condition 'input[length]=='\0'' is always true
     *  Condition 'input[length]=='\0'' is always true [knownConditionTrueFalse]
     */
    } else if (input[length] != '\0' || (length == sizeof input - 1U && input[length] == '\0')) {
        int ch;

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
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", has_valid_digit_frequencies(input) ? "true" : "false");
    return EXIT_SUCCESS;
}