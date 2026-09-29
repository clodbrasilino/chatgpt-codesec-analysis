#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str)
{
    const char *current = str;

    if (str == NULL) {
        return 0;
    }

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - str);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Failed to read input");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    size_t length = string_length(input);

    if (length > 0 && input[length - 1] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'input[length-1]' is assigned a value that is never used. [unreadVariable]
         */
        input[length - 1] = '\0';
        --length;
    }

    printf("%zu\n", length);
    return EXIT_SUCCESS;
}