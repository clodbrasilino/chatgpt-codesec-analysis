#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *string)
{
    bool found[5] = {false};

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        switch (tolower((unsigned char)*string)) {
        case 'a':
            found[0] = true;
            break;
        case 'e':
            found[1] = true;
            break;
        case 'i':
            found[2] = true;
            break;
        case 'o':
            found[3] = true;
            break;
        case 'u':
            found[4] = true;
            break;
        default:
            break;
        }

        if (found[0] && found[1] && found[2] && found[3] && found[4]) {
            return true;
        }

        ++string;
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return 1;
    }

    if (length == 0 && character == EOF) {
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
        capacity = new_capacity;
    }

    input[length] = '\0';

    if (contains_all_vowels(input)) {
        puts("Accepted");
    } else {
        puts("Rejected");
    }

    free(input);

    return ferror(stdout) ? 1 : 0;
}