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

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        input[0] = '\0';
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (printf("%zu\n", count_matching_positions(input)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}