#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool first_and_last_equal(const char *str)
{
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    size_t length = strlen(str);
    return str[0] == str[length - 1];
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof input - 1) {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }

        if (character != '\n') {
            return 1;
        }
    }

    if (length == 0) {
        return 1;
    }

    printf("%s\n", first_and_last_equal(input) ? "Equal" : "Not equal");
    return 0;
}