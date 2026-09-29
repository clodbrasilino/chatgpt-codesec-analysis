#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *str)
{
    unsigned int found = 0;
    const unsigned int all_vowels = 0x1FU;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        switch (tolower((unsigned char)*str)) {
        case 'a':
            found |= 1U << 0;
            break;
        case 'e':
            found |= 1U << 1;
            break;
        case 'i':
            found |= 1U << 2;
            break;
        case 'o':
            found |= 1U << 3;
            break;
        case 'u':
            found |= 1U << 4;
            break;
        default:
            break;
        }

        if (found == all_vowels) {
            return true;
        }

        ++str;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *line;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && ferror(stream)) {
                free(line);
                return NULL;
            }
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(line);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(line);
                return NULL;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (feof(stream) && length == 0) {
        free(line);
        return NULL;
    }

    line[length] = '\0';
    return line;
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