#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char seen[256] = {0};

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (const unsigned char *current = (const unsigned char *)str;
         *current != '\0';
         ++current) {
        if (seen[*current]) {
            *result = *current;
            return 1;
        }

        seen[*current] = 1;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    unsigned char repeated;
    if (find_first_repeated_character(input, &repeated)) {
        printf("%c\n", repeated);
    } else {
        puts("No repeated character");
    }

    free(input);
    return EXIT_SUCCESS;
}