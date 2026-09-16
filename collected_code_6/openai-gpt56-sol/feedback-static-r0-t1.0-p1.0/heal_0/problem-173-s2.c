#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_non_alphanumeric(char *string)
{
    unsigned char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = (unsigned char *)string;
    destination = string;

    while (*source != '\0') {
        if (isalnum(*source) != 0) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (length > 0 && line[(size_t)length - 1U] == '\n') {
        line[(size_t)length - 1U] = '\0';
    }

    remove_non_alphanumeric(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}