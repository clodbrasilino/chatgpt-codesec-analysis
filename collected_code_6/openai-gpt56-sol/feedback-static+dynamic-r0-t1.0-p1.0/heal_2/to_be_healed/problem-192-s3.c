#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_letter_and_number(const char *str)
{
    bool has_letter = false;
    bool has_number = false;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char character = (unsigned char)*str;

        if (isalpha(character)) {
            has_letter = true;
        } else if (isdigit(character)) {
            has_number = true;
        }

        if (has_letter && has_number) {
            return true;
        }

        ++str;
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return 1;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';

    if (has_letter_and_number(input)) {
        puts("The string contains at least one letter and one number.");
    } else {
        puts("The string does not contain at least one letter and one number.");
    }

    free(input);
    return 0;
}