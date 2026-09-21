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
        while (left < right && !is_vowel((unsigned char)str[left])) {
            ++left;
        }

        while (left < right &&
               !is_vowel((unsigned char)str[right - 1U])) {
            --right;
        }

        if (left < right) {
            char temporary = str[left];
            str[left] = str[right - 1U];
            str[right - 1U] = temporary;
            ++left;
            --right;
        }
    }
}

int main(void)
{
    const size_t maximum = (size_t)MAX_INPUT_LENGTH;
    char *line;
    size_t length = 0;
    int ch = EOF;

    if (maximum == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    line = malloc(maximum + 1U);
    if (line == NULL) {
        return EXIT_FAILURE;
    }

    while (length < maximum) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(line);
            return EXIT_FAILURE;
        }
    } else if (ch != '\n') {
        int extra = fgetc(stdin);

        if (extra != '\n' && extra != EOF) {
            free(line);
            return EXIT_FAILURE;
        }

        if (extra == EOF && ferror(stdin)) {
            free(line);
            return EXIT_FAILURE;
        }
    }

    line[length] = '\0';
    reverse_vowels(line, length);

    if (length != 0U && fwrite(line, 1U, length, stdout) != length) {
        free(line);
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}