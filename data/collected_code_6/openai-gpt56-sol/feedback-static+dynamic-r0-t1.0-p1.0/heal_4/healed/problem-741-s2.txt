#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    for (size_t i = 1; string[i] != '\0'; ++i) {
        if (string[i] != string[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        puts("False");
        return EXIT_SUCCESS;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    puts(all_characters_same(input) ? "True" : "False");

    free(input);
    return EXIT_SUCCESS;
}