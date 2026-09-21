#include <ctype.h>
#include <stdio.h>

static size_t last_word_length_stream(FILE *stream, int *error)
{
    size_t current_length = 0;
    size_t last_length = 0;
    int ch;

    *error = 0;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (isspace((unsigned char)ch)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            ++current_length;
        }
    }

    if (ferror(stream)) {
        *error = 1;
        return 0;
    }

    return current_length != 0 ? current_length : last_length;
}

int main(void)
{
    int error;
    size_t length = last_word_length_stream(stdin, &error);

    if (error) {
        return 1;
    }

    printf("%zu\n", length);
    return 0;
}