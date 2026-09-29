#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void capitalize_first_and_last(char *string)
{
    size_t i = 0;

    while (string[i] != '\0') {
        while (string[i] != '\0' && isspace((unsigned char)string[i])) {
            ++i;
        }

        if (string[i] == '\0') {
            break;
        }

        string[i] = (char)toupper((unsigned char)string[i]);

        while (string[i + 1] != '\0' &&
               !isspace((unsigned char)string[i + 1])) {
            ++i;
        }

        string[i] = (char)toupper((unsigned char)string[i]);
        ++i;
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (length > 0 && line[(size_t)length - 1] == '\n') {
        line[(size_t)length - 1] = '\0';
    }

    capitalize_first_and_last(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}