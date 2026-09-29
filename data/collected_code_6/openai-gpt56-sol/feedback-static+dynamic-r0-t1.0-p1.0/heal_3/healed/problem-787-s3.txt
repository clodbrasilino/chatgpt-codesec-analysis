#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int matches(const char *string)
{
    return string != NULL && strcmp(string, "abbb") == 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char input[MAX_INPUT_LENGTH + 1];
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length >= MAX_INPUT_LENGTH) {
            while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
            }
            return EXIT_FAILURE;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && length == 0) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(matches(input) ? "Match" : "No match");

    return EXIT_SUCCESS;
}