#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024

int replace_spaces(char *string, size_t length, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length = 0;
    int ch;
    int replacement_input;

    while (length < sizeof input - 1) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';

    if (ch == EOF && length == 0) {
        return EXIT_FAILURE;
    }

    if (ch != '\n' && ch != EOF) {
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF) {
            return EXIT_FAILURE;
        }
    }

    replacement_input = getchar();

    if (replacement_input == EOF || replacement_input == '\0') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, 1, length, stdout) != length || fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}