#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { INPUT_CAPACITY = 4096 };

static bool ends_with_number(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           isdigit((unsigned char)string[length - 1U]) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        input[0] = '\0';
    }

    size_t length = 0U;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    return EXIT_SUCCESS;
}