#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_non_alphanumeric(char *str)
{
    if (str == NULL) {
        return;
    }

    char *read_ptr = str;
    char *write_ptr = str;

    while (*read_ptr != '\0') {
        unsigned char ch = (unsigned char)*read_ptr;

        if (isalnum(ch) != 0) {
            *write_ptr++ = *read_ptr;
        }

        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        int status = ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    remove_non_alphanumeric(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}