#include <stdio.h>
#include <string.h>
#include <regex.h>

void clean_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char result[1024] = "";
    int pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", 0)) {
        return;
    }

    while (regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            size_t len = match[0].rm_so;
            if (strlen(result) + len < sizeof(result) - 1) {
                strncat(result, str + pos, len);
            }
        }
        pos += match[0].rm_eo;
    }

    if (pos < strlen(str)) {
        size_t len = strlen(str) - pos;
        if (strlen(result) + len < sizeof(result) - 1) {
            strncat(result, str + pos, len);
        }
    }

    strncpy(str, result, sizeof(result) - 1);
    str[sizeof(result) - 1] = '\0';
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input);
    printf("%s\n", input);
    return 0;
}