#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int i = 0;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    while (1) {
        int rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH) break;
        if (rc != 0) {
            regfree(&regex);
            return;
        }
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (match_len > 0 && match_len < 256) {
            char buffer[256];
            strncpy(buffer, str + i, match_len);
            buffer[match_len] = '\0';
            memmove(str + i + 1, str + i + match_len, strlen(str + i + match_len) + 1);
            str[i] = ':';
        }
        i += 1;
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}