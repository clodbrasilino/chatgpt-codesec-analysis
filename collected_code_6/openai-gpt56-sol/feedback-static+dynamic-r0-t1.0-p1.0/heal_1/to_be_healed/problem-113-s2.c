#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_integer(const char *string)
{
    const unsigned char *cursor;

    if (string == NULL || *string == '\0') {
        return false;
    }

    cursor = (const unsigned char *)string;

    if (*cursor == '+' || *cursor == '-') {
        ++cursor;
    }

    if (*cursor == '\0') {
        return false;
    }

    while (*cursor != '\0') {
        if (!isdigit(*cursor)) {
            return false;
        }
        ++cursor;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    size_t length = 0;
    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length == sizeof input - 1) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character == EOF && ferror(stdin)) {
            return 1;
        }

        puts("Not an integer");
        return 0;
    }

    input[length] = '\0';
    puts(is_integer(input) ? "Integer" : "Not an integer");

    return 0;
}