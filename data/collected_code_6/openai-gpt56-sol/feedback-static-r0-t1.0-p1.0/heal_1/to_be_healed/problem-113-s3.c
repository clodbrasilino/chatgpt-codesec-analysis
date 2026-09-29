#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_integer(const char *str)
{
    size_t i = 0;

    if (str == NULL || str[0] == '\0') {
        return false;
    }

    if (str[i] == '+' || str[i] == '-') {
        ++i;
    }

    if (str[i] == '\0') {
        return false;
    }

    for (; str[i] != '\0'; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return 1;
    } else if (!feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return 1;
        }

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }
    }

    if (printf("%s\n", is_integer(input) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}