#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *current = (unsigned char *)string;
         *current != '\0';
         ++current) {
        *current = (unsigned char)tolower(*current);
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        if (ferror(stdin)) {
            perror("getline");
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_SUCCESS;
    }

    if (string_to_lower(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fputs(input, stdout) == EOF) {
        perror("fputs");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}