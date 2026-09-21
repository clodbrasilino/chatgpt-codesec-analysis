#include <stdbool.h>
#include <stdio.h>

static bool matches(const char *string)
{
    if (string == NULL) {
        return false;
    }

    return (string[0] == 'a' && string[1] == '\0') ||
           (string[0] == 'a' && string[1] == 'b' && string[2] == '\0');
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

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length < sizeof input && input[length] == '\0') {
        int character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                perror("fgetc");
                return 1;
            }
        } else {
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
    } else {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(matches(input) ? "Match" : "No match");
    return 0;
}