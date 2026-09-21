#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(const char *string, unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || result == NULL) {
        return 0;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (seen[character]) {
            *result = character;
            return 1;
        }

        seen[character] = true;
        ++string;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    unsigned char repeated;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (first_repeated_character(input, &repeated)) {
        if (printf("%c\n", repeated) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated character\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}