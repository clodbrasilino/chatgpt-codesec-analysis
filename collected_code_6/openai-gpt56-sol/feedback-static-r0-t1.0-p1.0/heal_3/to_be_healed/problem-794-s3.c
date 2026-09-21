#include <stdbool.h>
#include <stdio.h>

enum {
    INPUT_CAPACITY = 1024
};

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    int ch = EOF;
    bool too_long = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    fputs("Input error\n", stderr);
                    return 1;
                }
            }

            break;
        }

        if (length < sizeof input) {
            input[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        perror("stdin");
        return 1;
    }

    if (too_long) {
        fputs("Input too long\n", stderr);
        return 1;
    }

    if (length == 0U && ch == EOF) {
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}