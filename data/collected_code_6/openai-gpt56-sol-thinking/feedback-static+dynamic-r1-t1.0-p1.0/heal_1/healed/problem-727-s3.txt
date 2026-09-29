#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int remove_non_alphanumeric(char *text)
{
    unsigned char *read_ptr;
    unsigned char *write_ptr;

    if (text == NULL) {
        return -1;
    }

    read_ptr = (unsigned char *)text;
    write_ptr = (unsigned char *)text;

    while (*read_ptr != '\0') {
        if (isalnum(*read_ptr)) {
            *write_ptr++ = *read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (remove_non_alphanumeric(argv[1]) != 0) {
        fputs("Failed to process input\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}