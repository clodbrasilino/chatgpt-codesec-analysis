#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int replace_with_colons(char *string)
{
    regex_t regex;
    regmatch_t match;
    char *cursor;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    cursor = string;

    while ((result = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        cursor[match.rm_so] = ':';
        cursor += match.rm_eo;
    }

    regfree(&regex);

    return result == REG_NOMATCH ? 0 : -1;
}

int main(void)
{
    char string[] = "Hello, world. This is a sample, string.";

    if (replace_with_colons(string) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}