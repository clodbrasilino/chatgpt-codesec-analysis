#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *str)
{
    unsigned int vowels = 0U;
    const unsigned int all_vowels = 0x1FU;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        switch (tolower((unsigned char)*str)) {
        case 'a':
            vowels |= 1U << 0;
            break;
        case 'e':
            vowels |= 1U << 1;
            break;
        case 'i':
            vowels |= 1U << 2;
            break;
        case 'o':
            vowels |= 1U << 3;
            break;
        case 'u':
            vowels |= 1U << 4;
            break;
        default:
            break;
        }

        if (vowels == all_vowels) {
            return true;
        }

        ++str;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t length = 0U;
    size_t capacity = 128U;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)(unsigned char)ch;
        ++length;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    puts(contains_all_vowels(input) ? "Accepted" : "Rejected");
    free(input);

    return EXIT_SUCCESS;
}