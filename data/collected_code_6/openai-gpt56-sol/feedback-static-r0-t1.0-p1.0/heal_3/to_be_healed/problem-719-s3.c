#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0') {
        if (length == sizeof input - 1) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                do {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = fgetc(stdin);
                } while (ch != '\n' && ch != EOF);

                return 1;
            }
        }
    } else {
        input[length] = '\0';
    }

    puts(matches_pattern(input) ? "Match" : "No match");
    return 0;
}