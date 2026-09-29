#include <stdbool.h>
#include <stdio.h>

#define WORD_CAPACITY 256U

static bool has_odd_length(const char *word, size_t length)
{
    return word != NULL && (length % 2U) != 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length >= sizeof word - 1U) {
            while (character != '\n' && character != EOF) {
                character = getchar();
            }
            return 1;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    word[length] = '\0';

    printf("%s\n", has_odd_length(word, length) ? "Odd" : "Even");
    return 0;
}