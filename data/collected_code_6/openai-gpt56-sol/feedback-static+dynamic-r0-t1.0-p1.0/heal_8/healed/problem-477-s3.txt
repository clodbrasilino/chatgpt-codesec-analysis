#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *p = (unsigned char *)string; *p != '\0'; ++p) {
        *p = (unsigned char)tolower(*p);
    }

    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&string, &capacity, stdin);

    if (length < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(string);
        return status;
    }

    if (string_to_lower(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    size_t output_length = (size_t)length;

    if (fwrite(string, 1, output_length, stdout) != output_length) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}