#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int matches(const char *string)
{
    return string != NULL && strcmp(string, "abbb") == 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 1];
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length >= MAX_INPUT_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
            }
            return EXIT_FAILURE;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && length == 0) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(matches(input) ? "Match" : "No match");

    return EXIT_SUCCESS;
}