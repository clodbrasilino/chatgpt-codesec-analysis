#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    size_t str_len = strlen(str);
    char *new_str = malloc(str_len + 1);
    if (new_str == NULL) return;
    new_str[str_len] = '\0';

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        free(new_str);
        return;
    }

    size_t i = 0, j = 0;
    while (regexec(&regex, str + i, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so + i;
        size_t match_end = pmatch[0].rm_eo + i;
        size_t copy_len = match_start - i;
        if (j + copy_len <= str_len) {
            memcpy(new_str + j, str + i, copy_len);
            j += copy_len;
        }
        if (j < str_len) {
            new_str[j++] = ':';
        }
        i = match_end;
    }
    size_t remaining = str_len - i;
    if (j + remaining <= str_len) {
        memcpy(new_str + j, str + i, remaining);
    }
    new_str[j] = '\0';

    strncpy(str, new_str, str_len + 1);
    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}