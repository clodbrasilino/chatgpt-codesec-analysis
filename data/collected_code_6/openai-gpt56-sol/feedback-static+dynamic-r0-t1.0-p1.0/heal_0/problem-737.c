#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static bool starts_with_vowel(const char *str)
{
    regex_t regex;
    int status;

    if (str == NULL) {
        return false;
    }

    status = regcomp(&regex, "^[AEIOUaeiou]", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    if (starts_with_vowel(input)) {
        puts("The string starts with a vowel.");
    } else {
        puts("The string does not start with a vowel.");
    }

    return 0;
}