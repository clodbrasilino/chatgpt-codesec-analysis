#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *str)
{
    unsigned int vowels = 0U;

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

        if (vowels == 0x1FU) {
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
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
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

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0U)) {
        free(buffer);
        return NULL;
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