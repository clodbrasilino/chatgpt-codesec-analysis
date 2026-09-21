#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str++ != 'a') {
        return false;
    }

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    enum { INPUT_SIZE = 1024 };
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0') {
        if (length == sizeof input - 1) {
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                do {
                    ch = fgetc(stdin);
                } while (ch != '\n' && ch != EOF);

                return 1;
            }
        }
    } else {
        input[length] = '\0';
    }

    puts(matches_pattern(input) ? "Match" : "No match");
    return 0;
}