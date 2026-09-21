#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_spaces_underscores(char *str, size_t len) {
    regex_t space_regex, underscore_regex;
    char tmp[1024];

    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        return;
    }

    if (regexec(&space_regex, str, 0, NULL, 0) == 0) {
        regmatch_t pmatch;
        int res = regexec(&space_regex, str, 1, &pmatch, 0);
        if (res == 0 && pmatch.rm_eo <= len) {
            size_t copy_len = pmatch.rm_so + 1 + (len - pmatch.rm_eo) + 1;
            snprintf(tmp, sizeof(tmp), "%.*s%s%s", (int)pmatch.rm_so, str, "_", str + pmatch.rm_eo);
            strncpy(str, tmp, copy_len > len ? len : copy_len);
            str[copy_len > len ? len : copy_len] = '\0';
        }
    }

    if (regexec(&underscore_regex, str, 0, NULL, 0) == 0) {
        regmatch_t pmatch;
        int res = regexec(&underscore_regex, str, 1, &pmatch, 0);
        if (res == 0 && pmatch.rm_eo <= len) {
            size_t copy_len = pmatch.rm_so + 1 + (len - pmatch.rm_eo) + 1;
            snprintf(tmp, sizeof(tmp), "%.*s%s%s", (int)pmatch.rm_so, str, " ", str + pmatch.rm_eo);
            strncpy(str, tmp, copy_len > len ? len : copy_len);
            str[copy_len > len ? len : copy_len] = '\0';
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