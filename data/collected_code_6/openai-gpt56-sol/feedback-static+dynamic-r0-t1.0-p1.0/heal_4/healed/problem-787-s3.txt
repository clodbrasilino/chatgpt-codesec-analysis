#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int matches(const char *string)
{
    return string != NULL && strcmp(string, "abbb") == 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4098 };
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0' && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != EOF && ch != '\n' && ch != '\r');

        return EXIT_FAILURE;
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    return EXIT_SUCCESS;
}