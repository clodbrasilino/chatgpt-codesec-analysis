#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_spaces(char *string, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

int main(void)
{
    char input[1024];
    int replacement_input;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == sizeof input - 1) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch != '\n') {
            return EXIT_FAILURE;
        }
    }

    replacement_input = getchar();

    if (replacement_input == EOF || replacement_input == '\0') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}