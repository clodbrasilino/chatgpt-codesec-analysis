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

        puts("No match");
        return EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int c = fgetc(stdin);

        if (c != '\n' && c != EOF) {
            do {
                c = fgetc(stdin);
            } while (c != '\n' && c != EOF);

            if (c == EOF && ferror(stdin)) {
                perror("fgetc");
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }

        if (c == EOF && ferror(stdin)) {
            perror("fgetc");
            return EXIT_FAILURE;
        }
    }

    puts(matches(input) ? "Match" : "No match");
    return EXIT_SUCCESS;
}