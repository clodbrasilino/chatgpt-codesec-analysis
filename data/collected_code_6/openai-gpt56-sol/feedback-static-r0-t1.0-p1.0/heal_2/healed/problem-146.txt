#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int print_ascii_values(const char *string)
{
    const unsigned char *current = (const unsigned char *)string;

    if (current == NULL) {
        return -1;
    }

    while (*current != '\0') {
        if (printf("%u\n", (unsigned int)*current) < 0) {
            return -1;
        }
        ++current;
    }

    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_string;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        free(string);
        return EXIT_FAILURE;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return EXIT_FAILURE;
        }
    }

    string[length] = '\0';

    if (print_ascii_values(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}