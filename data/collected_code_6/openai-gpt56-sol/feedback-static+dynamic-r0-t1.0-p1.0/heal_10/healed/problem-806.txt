#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)1048576)

static size_t max_uppercase_run(const char *str)
{
    size_t max_run = 0;
    size_t current_run = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            ++current_run;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
        ++str;
    }

    return max_run;
}

static int read_line(char *buffer, size_t capacity, FILE *stream)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity == 0 || stream == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            buffer[length] = '\0';
            return 1;
        }

        if (length >= capacity - 1) {
            do {
                ch = fgetc(stream);
            } while (ch != '\n' && ch != EOF);

            buffer[0] = '\0';

            if (ch == EOF && ferror(stream)) {
                return -1;
            }

            return -2;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return length == 0 ? 0 : 1;
}

int main(void)
{
    char *input;
    int status;

    input = malloc(MAX_INPUT_LENGTH + 1);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    status = read_line(input, MAX_INPUT_LENGTH + 1, stdin);
    if (status == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (status < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", max_uppercase_run(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}