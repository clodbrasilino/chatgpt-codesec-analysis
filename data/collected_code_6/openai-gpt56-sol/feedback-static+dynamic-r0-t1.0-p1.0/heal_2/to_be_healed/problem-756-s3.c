#include <stdbool.h>
#include <stdio.h>

static bool matches(const char *string)
{
    if (string == NULL) {
        return false;
    }

    return (string[0] == 'a' && string[1] == '\0') ||
           (string[0] == 'a' && string[1] == 'b' && string[2] == '\0');
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        return 0;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length < sizeof input && input[length] == '\0') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                perror("fgetc");
                return 1;
            }
        } else {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                perror("fgetc");
            } else {
                fputs("Input is too long\n", stderr);
            }
            return 1;
        }
    } else {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(matches(input) ? "Match" : "No match");
    return 0;
}