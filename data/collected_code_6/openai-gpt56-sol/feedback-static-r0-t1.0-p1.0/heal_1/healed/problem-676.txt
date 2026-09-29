#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_non_alphanumeric(char *string)
{
    unsigned char *read_pos = (unsigned char *)string;
    char *write_pos = string;

    while (*read_pos != '\0') {
        if (isalnum(*read_pos)) {
            *write_pos++ = (char)*read_pos;
        }
        ++read_pos;
    }

    *write_pos = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    remove_non_alphanumeric(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}