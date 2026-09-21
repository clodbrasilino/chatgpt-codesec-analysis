#include <stdio.h>
#include <string.h>
#include <regex.h>

void sanitize_str(char *str) {
    regex_t re;
    regmatch_t pmatch[1];
    int status, pos = 0;
    const char *pattern = "[^a-zA-Z0-9]";

    status = regcomp(&re, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[100];
        regerror(status, &re, error_message, 100);
        return;
    }

    while (regexec(&re, str + pos, 1, pmatch, 0) == 0) {
        size_t len = strlen(str + pos + pmatch[0].rm_eo);
        memmove(str + pos, str + pos + pmatch[0].rm_eo, len + 1);
    }

    regfree(&re);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_str(input);
    printf("%s\n", input);
    return 0;
}