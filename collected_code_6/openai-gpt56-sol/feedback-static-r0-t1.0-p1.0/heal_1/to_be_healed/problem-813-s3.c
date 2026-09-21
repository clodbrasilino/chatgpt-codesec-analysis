#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *string)
{
    const char *current;

    if (string == NULL) {
        return 0;
    }

    current = string;

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - string);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    size_t length = string_length(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'buffer[length-1]' is assigned a value that is never used. [unreadVariable]
         */
        buffer[length - 1] = '\0';
        --length;
    }

    printf("%zu\n", length);

    return EXIT_SUCCESS;
}