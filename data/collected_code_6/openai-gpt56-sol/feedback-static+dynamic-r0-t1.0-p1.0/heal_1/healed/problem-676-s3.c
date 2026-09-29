#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alphanumeric(char *string, size_t capacity)
{
    size_t source = 0;
    size_t destination = 0;
    size_t length;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(string, capacity);
    if (length == capacity) {
        return -1;
    }

    while (source < length) {
        unsigned char character = (unsigned char)string[source++];

        if (isalnum(character)) {
            string[destination++] = (char)character;
        }
    }

    string[destination] = '\0';
    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024 };
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        int result = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return result;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (remove_non_alphanumeric(input, INPUT_CAPACITY) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", input) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}