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
            char tmp = str[left];
            str[left] = str[right];
            str[right] = tmp;
            ++left;
            --right;
        }
    }
}

int main(void)
{
    char *line;
    size_t capacity = 128;
    size_t length = 0;
    const size_t limit = (size_t)MAX_INPUT_LENGTH + 1U;

    line = malloc(capacity);
    if (line == NULL) {
        return EXIT_FAILURE;
    }

    while (length < (size_t)MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && ferror(stdin)) {
                free(line);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity >= limit) {
                free(line);
                return EXIT_FAILURE;
            }

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            if (new_capacity > limit) {
                new_capacity = limit;
            }

            if (new_capacity <= capacity) {
                free(line);
                return EXIT_FAILURE;
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

    if (length == (size_t)MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != EOF && ch != '\n') {
            free(line);
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            free(line);
            return EXIT_FAILURE;
        }
    }

    line[length] = '\0';
    reverse_vowels(line, length);

    if (fwrite(line, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}