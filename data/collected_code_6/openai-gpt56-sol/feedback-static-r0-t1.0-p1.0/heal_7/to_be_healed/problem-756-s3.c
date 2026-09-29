#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches(const char *string)
{
    return string != NULL &&
           (strcmp(string, "a") == 0 || strcmp(string, "ab") == 0);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[3];
    size_t length = 0;
    int c;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (length < sizeof(input) - 1) {
            input[length++] = (char)c;
        } else {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = fgetc(stdin)) != '\n' && c != EOF) {
            }

            if (c == EOF && ferror(stdin)) {
                perror("fgetc");
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }
    }

    if (c == EOF && ferror(stdin)) {
        perror("fgetc");
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    return EXIT_SUCCESS;
}