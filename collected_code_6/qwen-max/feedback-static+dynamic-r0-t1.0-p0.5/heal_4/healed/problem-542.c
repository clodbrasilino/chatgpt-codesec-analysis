#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str, size_t len) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *ptr = str;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    while (regexec(&regex, ptr, 1, pmatch, 0) == 0 && len > 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (match_len > 0 && match_len <= len) {
            size_t remaining_len = len - (ptr - str);
            size_t new_len = remaining_len - match_len + 1;
            memmove(ptr + 1, ptr + match_len, new_len);
            *ptr = ':';
            ptr += 2;
            len -= (match_len - 1);
        } else {
            break;
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}