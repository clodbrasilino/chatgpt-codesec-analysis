#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int toggle_case(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (char *current = string; *current != '\0'; ++current) {
        unsigned char character = (unsigned char)*current;

        if (islower(character)) {
            *current = (char)toupper(character);
        } else if (isupper(character)) {
            *current = (char)tolower(character);
        }
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (toggle_case(line) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}