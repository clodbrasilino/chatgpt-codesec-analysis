#include <ctype.h>
#include <stdio.h>

static size_t last_word_length(void)
{
    size_t current_length = 0;
    size_t last_length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (isspace((unsigned char)ch)) {
            if (current_length > 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            ++current_length;
        }
    }

    if (current_length > 0) {
        last_length = current_length;
    }

    return last_length;
}

int main(void)
{
    size_t length = last_word_length();

    if (ferror(stdin)) {
        return 1;
    }

    printf("%zu\n", length);
    return 0;
}