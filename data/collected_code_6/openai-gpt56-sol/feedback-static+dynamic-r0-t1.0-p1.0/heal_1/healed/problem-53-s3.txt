#include <stdio.h>
#include <string.h>

#define STRING_CAPACITY 1024U

static int first_and_last_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

int main(void)
{
    char string[STRING_CAPACITY];
    size_t length;

    if (fgets(string, (int)sizeof string, stdin) == NULL) {
        return 1;
    }

    length = strnlen(string, sizeof string);

    if (length == sizeof string) {
        return 1;
    }

    if (length > 0U && string[length - 1U] == '\n') {
        string[--length] = '\0';
    } else if (length == sizeof string - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character == EOF) {
            return 1;
        }
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");
    return 0;
}