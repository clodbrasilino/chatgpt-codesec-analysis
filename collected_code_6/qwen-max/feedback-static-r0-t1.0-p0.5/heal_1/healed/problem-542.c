#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti;
    char *ptr = str;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    while ((reti = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
        size_t len = strlen(ptr + pmatch[0].rm_eo);
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, len + 1);
        *ptr = ':';
        ptr += 2;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}