#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static int last_word_length_stream(FILE *stream, size_t *length)
{
    size_t current_length = 0;
    size_t last_length = 0;
    int ch;

    if (stream == NULL || length == NULL) {
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
            ++current_length;
        }
    }

    if (ferror(stream)) {
        return -1;
    }

    *length = current_length != 0 ? current_length : last_length;
    return 0;
}

int main(void)
{
    size_t length;

    if (last_word_length_stream(stdin, &length) != 0) {
        return 1;
    }

    if (printf("%zu\n", length) < 0) {
        return 1;
    }

    return 0;
}