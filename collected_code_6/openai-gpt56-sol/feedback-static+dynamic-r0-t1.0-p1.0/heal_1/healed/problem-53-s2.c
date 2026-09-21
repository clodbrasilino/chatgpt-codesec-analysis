#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

int main(void)
{
    char input[1024];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    length = strcspn(input, "\r\n");

    if (input[length] != '\0') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        return 1;
    }

    if (first_and_last_are_equal(input, length)) {
        puts("Equal");
    } else {
        puts("Not equal");
    }

    return 0;
}