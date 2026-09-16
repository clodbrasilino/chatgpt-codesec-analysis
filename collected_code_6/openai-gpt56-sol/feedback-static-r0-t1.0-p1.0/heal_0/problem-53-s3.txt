#include <stdio.h>
#include <string.h>

static int first_and_last_equal(const char *string)
{
    size_t length;

    if (string == NULL) {
        return 0;
    }

    length = strlen(string);
    return length > 0U && string[0] == string[length - 1U];
}

int main(void)
{
    char string[1024];
    size_t length;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    length = strlen(string);
    if (length > 0U && string[length - 1U] == '\n') {
        string[--length] = '\0';
    } else if (length == sizeof string - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            return 1;
        }
    }

    puts(first_and_last_equal(string) ? "Equal" : "Not equal");
    return 0;
}