#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <regex.h>

void replace_with_colon(char *str)
{
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[ ,.]", REG_EXTENDED);

    if (reti != 0) {
        fprintf(stderr, "regcomp failed\n");
        return;
    }

    char *cursor = str;
    regmatch_t match;

    while ((reti = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        cursor[match.rm_so] = ':';
        cursor += match.rm_so + 1;
    }

    if (reti != REG_NOMATCH) {
        fprintf(stderr, "regexec failed\n");
    }

    regfree(&regex);
}

int main(void)
{
    char text[] = "Hello, world. This is a test, with spaces...";
    replace_with_colon(text);
    printf("%s\n", text);
    return 0;
}