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
    char input[4];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        return 0;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            perror("fgetc");
        } else {
            fputs("Input is too long\n", stderr);
        }

        return 1;
    }

    puts(matches(input) ? "Match" : "No match");
    return 0;
}