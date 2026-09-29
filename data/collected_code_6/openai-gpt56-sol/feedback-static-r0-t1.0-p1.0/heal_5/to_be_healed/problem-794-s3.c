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
    char input[INPUT_CAPACITY + 1U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("stdin");
            return 1;
        }
        return 0;
    }

    size_t length = 0U;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (length < sizeof input &&
        (input[length] == '\n' || input[length] == '\r')) {
        input[length] = '\0';
    } else if (length == INPUT_CAPACITY) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != '\r' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != '\r' && ch != EOF) {
            }

            if (ferror(stdin)) {
                perror("stdin");
                return 1;
            }

            fputs("Input too long\n", stderr);
            return 1;
        }
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}