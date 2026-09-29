#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool first_and_last_are_equal(const char *string)
{
    size_t length;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);

    if (length == 0U) {
        return false;
    }

    return string[0] == string[length - 1U];
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (first_and_last_are_equal(input)) {
        puts("Equal");
    } else {
        puts("Not equal");
    }

    return 0;
}