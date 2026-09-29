#include <stdio.h>
#include <string.h>
#include <regex.h>

void clean_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char result[1024] = "";
    int pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED)) {
        return;
    }

    while (regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0 && (pos + match[0].rm_so) < 1024) {
            size_t len = snprintf(result + strlen(result), 1024 - strlen(result) - 1, "%.*s", match[0].rm_so, str + pos);
            (void)len;
        }
        pos += match[0].rm_eo;
    }

    if (pos < (int)strlen(str) && (strlen(result) + strlen(str + pos) + 1) < 1024) {
        size_t len = snprintf(result + strlen(result), 1024 - strlen(result) - 1, "%s", str + pos);
        (void)len;
    }

    strncpy(str, result, 1023);
    str[1023] = '\0';
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input);
    printf("%s\n", input);
    return 0;
}