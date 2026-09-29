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

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
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

        if (ferror(stdin)) {
            perror("fgetc");
            return EXIT_FAILURE;
        }
    }

    puts(matches(input) ? "Match" : "No match");
    return EXIT_SUCCESS;
}