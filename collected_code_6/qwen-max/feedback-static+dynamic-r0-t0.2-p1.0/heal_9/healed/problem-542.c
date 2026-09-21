#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str, size_t str_len) {
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) return;

    char *new_str = malloc(str_len + 1);
    if (!new_str) return;

    size_t new_index = 0;
    for (size_t i = 0; ; i++) {
        int rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH || pmatch[0].rm_so == -1) break;

        size_t len = pmatch[0].rm_so;
        size_t match_end = i + pmatch[0].rm_eo;

        memcpy(new_str + new_index, str + i, len);
        new_index += len;
        new_str[new_index++] = ':';

        i += len + 1;
    }

    size_t remaining_len = str_len - (i - pmatch[0].rm_eo);
    if (remaining_len > 0) {
        memcpy(new_str + new_index, str + i, remaining_len);
        new_index += remaining_len;
    }

    new_str[new_index] = '\0';
    strncpy(str, new_str, str_len + 1);
    free(new_str);

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}