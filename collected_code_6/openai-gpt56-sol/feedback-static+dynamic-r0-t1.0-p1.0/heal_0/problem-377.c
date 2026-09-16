#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_character(char *string, char character)
{
    char *source = string;
    char *destination = string;

    if (string == NULL) {
        return;
    }

    while (*source != '\0') {
        if (*source != character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    int input;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[--length] = '\0';
    }

    input = getchar();
    if (input == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, (char)input);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}