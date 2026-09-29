#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool has_letter_and_number(const char *string)
{
    if (string == NULL) {
        return false;
    }

    bool has_letter = false;
    bool has_number = false;

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string++;

        if (isalpha(character)) {
            has_letter = true;
        } else if (isdigit(character)) {
            has_number = true;
        }

        if (has_letter && has_number) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return 1;
    }

    if (character == EOF && length == 0) {
        free(input);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            return 1;
        }

        input = resized;
    }

    input[length] = '\0';
    puts(has_letter_and_number(input) ? "true" : "false");

    free(input);
    return 0;
}