#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *str)
{
    unsigned int found = 0U;
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
    char *line;
    size_t length = 0U;
    size_t capacity = 128U;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0U) {
                free(line);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2U;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    puts(contains_all_vowels(input) ? "Accepted" : "Rejected");

    free(input);
    return EXIT_SUCCESS;
}