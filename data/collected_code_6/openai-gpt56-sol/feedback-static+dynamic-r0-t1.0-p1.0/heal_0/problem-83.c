#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + (unsigned char)*string) % 256U;
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        input[0] = '\0';
    }

    size_t length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return EXIT_FAILURE;
    }

    unsigned char result = add_characters(input);

    if (printf("%c\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}