#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

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

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U >= sizeof input) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    replacement_input = fgetc(stdin);
    if (replacement_input == EOF ||
        replacement_input == '\0' ||
        replacement_input == '\n') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, 1U, length, stdout) != length) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}