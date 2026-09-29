#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 1024U

static int discard_line(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'input[length]' is assigned a value that is never used. [unreadVariable]
         */
        input[length] = '\0';
    } else if (discard_line() != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}