#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length;
    int replacement_input;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (length = 0U;
         length < sizeof input && input[length] != '\0' && input[length] != '\n';
         ++length) {
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (discard_line(stdin) != 0) {
        return EXIT_FAILURE;
    } else {
        return EXIT_FAILURE;
    }

    replacement_input = fgetc(stdin);
    if (replacement_input == EOF ||
        replacement_input == '\0' ||
        replacement_input == '\n') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, sizeof input[0], length, stdout) != length) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}