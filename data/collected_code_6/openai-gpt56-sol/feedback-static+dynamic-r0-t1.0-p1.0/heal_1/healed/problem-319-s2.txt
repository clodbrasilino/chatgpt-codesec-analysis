#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int find_five_letter_words(const char *text)
{
    const unsigned char *cursor = (const unsigned char *)text;
    const unsigned char *word_start = NULL;
    size_t word_length = 0;

    if (text == NULL) {
        return -1;
    }

    for (;;) {
        unsigned char c = *cursor;
        int is_letter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');

        if (is_letter) {
            if (word_length == 0) {
                word_start = cursor;
            }
            ++word_length;
        } else {
            if (word_length == 5) {
                if (fwrite(word_start, 1, word_length, stdout) != word_length ||
                    fputc('\n', stdout) == EOF) {
                    return -1;
                }
            }

            word_start = NULL;
            word_length = 0;

            if (c == '\0') {
                break;
            }
        }

        ++cursor;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_five_letter_words(input);
    free(input);

    if (result != 0) {
        fputs("Failed to process input\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}