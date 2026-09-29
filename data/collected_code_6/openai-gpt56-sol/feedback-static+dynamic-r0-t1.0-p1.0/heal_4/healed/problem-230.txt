#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    size_t i;

    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    char *newline;
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL || capacity < 2U) {
        return -1;
    }

    buffer[0] = '\0';
    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        *length = (size_t)(newline - buffer);
        return 0;
    }

    used = strnlen(buffer, capacity);
    if (used >= capacity) {
        buffer[0] = '\0';
        return -1;
    }

    if (used == capacity - 1U) {
        ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                return -1;
            }

            buffer[0] = '\0';
            return -1;
        }

        if (ch == EOF && ferror(stdin)) {
            return -1;
        }
    }

    *length = used;
    return 0;
}

static int read_replacement(char *replacement)
{
    int ch;
    int extra;

    if (replacement == NULL) {
        return -1;
    }

    ch = getchar();
    if (ch == EOF || ch == '\n' || ch == '\0') {
        return -1;
    }

    extra = getchar();
    if (extra != '\n' && extra != EOF) {
        if (discard_line() != 0) {
            return -1;
        }

        return -1;
    }

    if (extra == EOF && ferror(stdin)) {
        return -1;
    }

    *replacement = (char)ch;
    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    char replacement;
    size_t length;

    if (read_line(input, sizeof input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_replacement(&replacement) != 0) {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, replacement) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, sizeof input[0], length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}