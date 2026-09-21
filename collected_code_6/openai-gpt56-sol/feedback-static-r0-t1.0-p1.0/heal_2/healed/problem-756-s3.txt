#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { INPUT_SIZE = 1024 };

static bool matches(const char *string)
{
    return string != NULL &&
           (strcmp(string, "a") == 0 || strcmp(string, "ab") == 0);
}

int main(void)
{
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        return 0;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        fputs("Input is too long\n", stderr);
        return 1;
    }

    puts(matches(input) ? "Match" : "No match");
    return 0;
}