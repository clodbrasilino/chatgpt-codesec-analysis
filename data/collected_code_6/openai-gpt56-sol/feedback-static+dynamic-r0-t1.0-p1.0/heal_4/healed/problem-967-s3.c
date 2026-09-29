#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool contains_all_vowels(const char *string)
{
    unsigned int found = 0U;

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        switch (tolower((unsigned char)*string)) {
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

        if (found == 0x1FU) {
            return true;
        }

        ++string;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length > SIZE_MAX - 2U) {
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity = capacity == 0U ? 128U : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);
        if (buffer == NULL) {
            return NULL;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(contains_all_vowels(input) ? "Accepted" : "Rejected") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}