#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches(const char *string)
{
    return string != NULL &&
           (strcmp(string, "a") == 0 || strcmp(string, "ab") == 0);
}

int main(void)
{
    char input[3];
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length < sizeof(input) - 1) {
            input[length++] = (char)character;
        } else {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                perror("fgetc");
            } else {
                fputs("Input is too long\n", stderr);
            }

            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        return EXIT_SUCCESS;
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    return EXIT_SUCCESS;
}