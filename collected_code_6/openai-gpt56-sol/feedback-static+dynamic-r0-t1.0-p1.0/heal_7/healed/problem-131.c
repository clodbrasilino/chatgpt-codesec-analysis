#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static int is_vowel(unsigned char c)
{
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}

static void reverse_vowels(char *str, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (str == NULL || length < 2U) {
        return;
    }

    while (left < right) {
        do {
            --right;
        } while (left < right &&
                 !is_vowel((unsigned char)str[right]));

        while (left < right &&
               !is_vowel((unsigned char)str[left])) {
            ++left;
        }

        if (left < right) {
            char tmp = str[left];
            str[left] = str[right];
            str[right] = tmp;
            ++left;
        }
    }
}

int main(void)
{
    const size_t maximum = (size_t)MAX_INPUT_LENGTH;
    char *line = malloc(maximum + 1U);
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length >= maximum) {
            free(line);
            return EXIT_FAILURE;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return EXIT_FAILURE;
    }

    line[length] = '\0';
    reverse_vowels(line, length);

    if (fwrite(line, sizeof *line, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}