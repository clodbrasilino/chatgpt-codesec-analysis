#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int is_vowel(unsigned char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

static void reverse_vowels(char *str, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (str == NULL) {
        return;
    }

    while (left < right) {
        while (left < right && !is_vowel((unsigned char)str[left])) {
            ++left;
        }

        while (left < right && !is_vowel((unsigned char)str[right - 1])) {
            --right;
        }

        if (left < right) {
            char temp = str[left];
            str[left] = str[right - 1];
            str[right - 1] = temp;
            ++left;
            --right;
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t input_length = getline(&line, &capacity, stdin);

    if (input_length < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return status;
    }

    size_t length = (size_t)input_length;

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';

        if (length > 0 && line[length - 1] == '\r') {
            line[--length] = '\0';
        }
    }

    reverse_vowels(line, length);

    if (fwrite(line, 1, length, stdout) != length || fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}