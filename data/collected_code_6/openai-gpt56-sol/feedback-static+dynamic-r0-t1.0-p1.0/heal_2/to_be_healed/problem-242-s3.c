#include <stdio.h>
#include <stdlib.h>

size_t count_characters(const char *string, size_t capacity)
{
    size_t length = 0;

    if (string == NULL) {
        return 0;
    }

    while (length < capacity && string[length] != '\0') {
        ++length;
    }

    return length;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    length = count_characters(input, sizeof input);

    if (length > 0 && input[length - 1] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'input[--length]' is assigned a value that is never used. [unreadVariable]
         */
        input[--length] = '\0';
    } else if (length == sizeof input - 1) {
        int character;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}