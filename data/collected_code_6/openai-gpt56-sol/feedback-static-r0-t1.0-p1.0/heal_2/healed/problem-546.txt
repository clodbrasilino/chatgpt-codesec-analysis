#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char *find_last_char(const char *string, int character)
{
    if (string == NULL) {
        return NULL;
    }

    return strrchr(string, (unsigned char)character);
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int input;
    int character;
    const char *result;

    while ((input = getchar()) != '\n' && input != EOF) {
        if (length == SIZE_MAX - 1) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = length + 2;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                free(string);
                return EXIT_FAILURE;
            }

            char *temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)input;
    }

    if (input == EOF && length == 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length >= capacity) {
        char *temporary = realloc(string, length + 1);
        if (temporary == NULL) {
            free(string);
            return EXIT_FAILURE;
        }
        string = temporary;
    }

    string[length] = '\0';

    character = getchar();
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