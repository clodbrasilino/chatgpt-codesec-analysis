#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
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

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    int ch;
    size_t used = 0;

    if (buffer == NULL || length == NULL || capacity == 0) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (used + 1 >= capacity) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            buffer[0] = '\0';
            *length = 0;
            return -1;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *length = used;

    if (ch == EOF && used == 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length;
    int replacement_input;
    int ch;

    if (read_line(input, sizeof input, &length) != 0) {
        return EXIT_FAILURE;
    }

    replacement_input = getchar();
    if (replacement_input == EOF || replacement_input == '\0' ||
        replacement_input == '\n') {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (replace_spaces(input, length, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, sizeof input[0], length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}