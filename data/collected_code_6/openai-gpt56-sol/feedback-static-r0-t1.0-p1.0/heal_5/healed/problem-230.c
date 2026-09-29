#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_SIZE, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (discard_line(stdin) != 0) {
                free(input);
                return EXIT_FAILURE;
            }

            free(input);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    int replacement_input = fgetc(stdin);

    if (replacement_input == EOF ||
        replacement_input == '\0' ||
        replacement_input == '\n') {
        free(input);
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, (char)replacement_input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fwrite(input, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}