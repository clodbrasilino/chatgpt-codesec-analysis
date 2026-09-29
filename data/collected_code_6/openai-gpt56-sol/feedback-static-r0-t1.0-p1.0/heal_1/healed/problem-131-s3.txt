#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int is_vowel(unsigned char character)
{
    switch (tolower(character)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return 1;
        default:
            return 0;
    }
}

static void reverse_vowels(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (string == NULL || length == 0) {
        return;
    }

    while (left < right) {
        while (left < right && !is_vowel((unsigned char)string[left])) {
            ++left;
        }

        while (left < right &&
               !is_vowel((unsigned char)string[right - 1])) {
            --right;
        }

        if (left < right) {
            char temporary = string[left];
            string[left] = string[right - 1];
            string[right - 1] = temporary;
            ++left;
            --right;
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t text_length;
    ssize_t input_length;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return status;
    }

    text_length = (size_t)input_length;

    if (text_length > 0 && line[text_length - 1] == '\n') {
        --text_length;
        line[text_length] = '\0';

        if (text_length > 0 && line[text_length - 1] == '\r') {
            --text_length;
            line[text_length] = '\0';
        }
    }

    reverse_vowels(line, text_length);

    if (fwrite(line, 1, text_length, stdout) != text_length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}