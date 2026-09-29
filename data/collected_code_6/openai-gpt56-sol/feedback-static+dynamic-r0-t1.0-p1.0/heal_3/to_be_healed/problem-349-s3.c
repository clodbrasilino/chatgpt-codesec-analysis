#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    for (; *str != '\0'; ++str) {
        if (*str != '0' && *str != '1') {
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
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0U;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }

        fputs("Not a binary string\n", stdout);
        return 0;
    }

    if (is_binary_string(input)) {
        fputs("Binary string\n", stdout);
    } else {
        fputs("Not a binary string\n", stdout);
    }

    return 0;
}