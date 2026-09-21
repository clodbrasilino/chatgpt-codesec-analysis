#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    size_t right;

    if (str == NULL || length < 2) {
        return;
    }

    right = length - 1;

    while (left < right) {
        while (left < right && !is_vowel((unsigned char)str[left])) {
            ++left;
        }

        while (left < right && !is_vowel((unsigned char)str[right])) {
            --right;
        }

        if (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            ++left;
            --right;
        }
    }
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line = malloc(capacity);

    if (line == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(line);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return EXIT_FAILURE;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(line);
        return EXIT_FAILURE;
    }

    line[length] = '\0';
    reverse_vowels(line, length);

    if (fwrite(line, 1, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}