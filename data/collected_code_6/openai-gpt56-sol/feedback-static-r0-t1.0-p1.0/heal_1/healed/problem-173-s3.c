#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
        if (isalnum(*source)) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        int failed = ferror(stdin);
        free(input);
        return failed ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    remove_non_alphanumeric(input);

    if (printf("%s\n", input) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}