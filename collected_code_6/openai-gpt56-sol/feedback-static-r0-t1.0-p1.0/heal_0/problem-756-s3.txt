#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches(const char *string)
{
    if (string == NULL) {
        return false;
    }

    return strcmp(string, "a") == 0 || strcmp(string, "ab") == 0;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        return 0;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            perror("getchar");
        } else {
            fputs("Input is too long\n", stderr);
        }

        return 1;
    }

    puts(matches(input) ? "Match" : "No match");
    return 0;
}