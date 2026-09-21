#include <stdio.h>
#include <stdbool.h>

bool first_and_last_equal(const char *str, size_t length)
{
    return str != NULL && length > 0 && str[0] == str[length - 1];
}

int main(void)
{
    char input[1024];
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length >= sizeof input) {
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            return 1;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        return 1;
    }

    printf("%s\n",
           first_and_last_equal(input, length) ? "Equal" : "Not equal");

    return 0;
}