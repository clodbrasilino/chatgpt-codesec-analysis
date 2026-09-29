#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static int length_of_last_word(FILE *stream, size_t *result)
{
    size_t last_length = 0;
    size_t current_length = 0;
    int ch = EOF;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (isspace((unsigned char)ch)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            if (current_length == SIZE_MAX) {
                return -1;
            }
            current_length++;
        }
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    *result = current_length != 0 ? current_length : last_length;
    return 0;
}

int main(void)
{
    size_t result;

    if (length_of_last_word(stdin, &result) != 0) {
        return 1;
    }

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}