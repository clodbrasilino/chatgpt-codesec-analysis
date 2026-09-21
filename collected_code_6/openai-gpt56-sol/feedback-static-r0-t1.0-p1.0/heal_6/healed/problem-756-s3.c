#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
    int c;

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (length < sizeof(input) - 1) {
            input[length++] = (char)c;
        } else {
            while ((c = fgetc(stdin)) != '\n' && c != EOF) {
            }

            if (c == EOF && ferror(stdin)) {
                perror("fgetc");
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }
    }

    if (c == EOF && ferror(stdin)) {
        perror("fgetc");
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    return EXIT_SUCCESS;
}