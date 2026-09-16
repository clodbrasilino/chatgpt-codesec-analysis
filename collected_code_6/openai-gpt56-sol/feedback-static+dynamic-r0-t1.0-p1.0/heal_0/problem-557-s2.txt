#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void toggle_case(char *string)
{
    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (islower(character)) {
            string[i] = (char)toupper(character);
        } else if (isupper(character)) {
            string[i] = (char)tolower(character);
        }
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

    toggle_case(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}