#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_spaces_underscores(char *str, size_t len) {
    regex_t space_regex, underscore_regex;
    char tmp[1024];
    regmatch_t pmatch;

    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        return;
    }

    while (regexec(&space_regex, str, 1, &pmatch, 0) == 0 && pmatch.rm_eo <= len) {
        size_t copy_len = pmatch.rm_so + 1 + (len - pmatch.rm_eo);
        snprintf(tmp, sizeof(tmp), "%.*s_%s", (int)pmatch.rm_so, str, str + pmatch.rm_eo);
        if (copy_len + 1 <= len) {
            strncpy(str, tmp, copy_len);
            str[copy_len] = '\0';
        }
    }

    while (regexec(&underscore_regex, str, 1, &pmatch, 0) == 0 && pmatch.rm_eo <= len) {
        size_t copy_len = pmatch.rm_so + 1 + (len - pmatch.rm_eo);
        snprintf(tmp, sizeof(tmp), "%.*s %s", (int)pmatch.rm_so, str, str + pmatch.rm_eo);
        if (copy_len + 1 <= len) {
            strncpy(str, tmp, copy_len);
            str[copy_len] = '\0';
        }
    }

    regfree(&space_regex);
    regfree(&underscore_regex);
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    size_t len = sizeof(test_str) / sizeof(test_str[0]) - 1;

    swap_spaces_underscores(test_str, len);

    printf("%s\n", test_str);

    return 0;
}