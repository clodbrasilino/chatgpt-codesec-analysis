#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, unsigned char character)
{
    unsigned char *read_ptr = (unsigned char *)string;
    unsigned char *write_ptr = (unsigned char *)string;

    while (*read_ptr != '\0') {
        if (*read_ptr != character) {
            *write_ptr++ = *read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    int input;

    length = getline(&string, &capacity, stdin);
    if (length == -1) {
        free(string);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (string[length - 1] == '\n' || string[length - 1] == '\r')) {
        string[--length] = '\0';
    }

    input = fgetc(stdin);
    if (input == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, (unsigned char)input);

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}