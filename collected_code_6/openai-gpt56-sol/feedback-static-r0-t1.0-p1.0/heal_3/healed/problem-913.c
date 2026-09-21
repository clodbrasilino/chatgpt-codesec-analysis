#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool ends_with_number(int character)
{
    return character != EOF && isdigit((unsigned char)character) != 0;
}

int main(void)
{
    char buffer[4096];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }

        return puts("false") == EOF ? 1 : 0;
    }

    size_t length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return 1;
    }

    bool truncated = length > 0 &&
                     buffer[length - 1] != '\n' &&
                     !feof(stdin);

    if (truncated) {
        int character;
        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        return 1;
    }

    while (length > 0 &&
           (buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
        --length;
    }

    bool result = length > 0 &&
                  ends_with_number((unsigned char)buffer[length - 1]);

    return puts(result ? "true" : "false") == EOF ? 1 : 0;
}