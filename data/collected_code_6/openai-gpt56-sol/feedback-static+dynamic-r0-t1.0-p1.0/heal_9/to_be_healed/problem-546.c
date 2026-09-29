#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static const char *find_last_char(const char *string, int character)
{
    if (string == NULL || character == EOF) {
        return NULL;
    }

    return strrchr(string, (unsigned char)character);
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *string = malloc(capacity);
    int character;
    const char *result;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    string[0] = '\0';

    for (;;) {
        size_t available;
        const char *newline;
        size_t added;

        if (capacity - length < 2) {
            size_t new_capacity;
            char *resized;

            if (capacity >= (size_t)INT_MAX) {
                free(string);
                return EXIT_FAILURE;
            }

            if (capacity > SIZE_MAX / 2) {
                new_capacity = (size_t)INT_MAX;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity > (size_t)INT_MAX) {
                    new_capacity = (size_t)INT_MAX;
                }
            }

            if (new_capacity <= capacity) {
                free(string);
                return EXIT_FAILURE;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        available = capacity - length;
        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        if (fgets(string + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        newline = memchr(string + length, '\n', available - 1);
        if (newline != NULL) {
            length = (size_t)(newline - string);
            string[length] = '\0';
            break;
        }

        added = strnlen(string + length, available - 1);
        if (added == available - 1 && string[length + added] != '\0') {
            free(string);
            return EXIT_FAILURE;
        }

        length += added;

        if (feof(stdin)) {
            break;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(stdin);
    if (character == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    result = find_last_char(string, character);

    if (result == NULL) {
        puts("Character not found");
    } else {
        printf("%td\n", result - string);
    }

    free(string);
    return EXIT_SUCCESS;
}