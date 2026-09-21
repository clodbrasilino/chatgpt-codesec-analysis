#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int toggle_case(char *str)
{
    if (str == NULL) {
        return -1;
    }

    for (; *str != '\0'; ++str) {
        unsigned char ch = (unsigned char)*str;

        if (islower(ch)) {
            *str = (char)toupper(ch);
        } else if (isupper(ch)) {
            *str = (char)tolower(ch);
        }
    }

    return 0;
}

int main(void)
{
    enum { BUFFER_SIZE = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (toggle_case(buffer) != 0) {
        fputs("Invalid string\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(buffer, stdout) == EOF) {
        perror("fputs");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}