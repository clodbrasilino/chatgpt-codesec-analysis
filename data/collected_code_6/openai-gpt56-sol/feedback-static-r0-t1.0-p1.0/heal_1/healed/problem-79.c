#include <stdio.h>

static int has_odd_length(const char *word, size_t length)
{
    return word != NULL && (length % 2U) != 0U;
}

int main(void)
{
    char word[256];
    size_t length = 0U;
    int character;
    int truncated = 0;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (character == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length < sizeof word - 1U) {
            word[length++] = (char)character;
        } else {
            truncated = 1;
        }
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        return 1;
    }

    if (truncated) {
        return 1;
    }

    word[length] = '\0';

    printf("%s\n", has_odd_length(word, length) ? "Odd" : "Even");

    return 0;
}