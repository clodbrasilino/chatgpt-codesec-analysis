#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < 26 && str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (tolower(ch) == 'a' + (int)i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char input[27];
    size_t length = 0;
    int ch;

    while (length < sizeof(input) - 1 &&
           (ch = getchar()) != '\n' &&
           ch != EOF) {
        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof(input) - 1 && ch != '\n' && ch != EOF) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (printf("%zu\n", count_matching_positions(input)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}