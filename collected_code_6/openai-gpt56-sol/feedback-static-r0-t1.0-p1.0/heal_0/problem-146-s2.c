#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_ascii_values(const char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        printf("%u\n", (unsigned int)(unsigned char)string[i]);
    }

    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&string, &capacity, stdin);

    if (length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }

    if (print_ascii_values(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}