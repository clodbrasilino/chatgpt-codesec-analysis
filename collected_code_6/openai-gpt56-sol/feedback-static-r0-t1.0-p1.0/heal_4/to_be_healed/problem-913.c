#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool ends_with_number(int character)
{
    return character != EOF && isdigit((unsigned char)character) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }

        return puts("false") == EOF ? 1 : 0;
    }

    size_t length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return 1;
    }

    bool truncated = length > 0 &&
                     buffer[length - 1] != '\n' &&
                     !feof(stdin);

    if (truncated) {
        int character;
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        return 1;
    }

    while (length > 0 &&
           (buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
        --length;
    }

    bool result = length > 0 &&
                  ends_with_number((unsigned char)buffer[length - 1]);

    return puts(result ? "true" : "false") == EOF ? 1 : 0;
}