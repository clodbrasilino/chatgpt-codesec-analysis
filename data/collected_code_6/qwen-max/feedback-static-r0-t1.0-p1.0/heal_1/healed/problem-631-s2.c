#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_spaces_underscores(char *str) {
    regex_t space_regex, underscore_regex;
    char tmp[1024];

    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        return;
    }

    if (regexec(&space_regex, str, 0, NULL, 0) == 0) {
        regmatch_t pmatch;
        int res = regexec(&space_regex, str, 1, &pmatch, 0);
        if (res == 0) {
            snprintf(tmp, sizeof(tmp), "%.*s%s%s", (int)pmatch.rm_so, str, "_", str + pmatch.rm_eo);
            strncpy(str, tmp, sizeof(tmp) - 1);
            str[sizeof(tmp) - 1] = '\0';
        }
    }

    if (regexec(&underscore_regex, str, 0, NULL, 0) == 0) {
        regmatch_t pmatch;
        int res = regexec(&underscore_regex, str, 1, &pmatch, 0);
        if (res == 0) {
            snprintf(tmp, sizeof(tmp), "%.*s%s%s", (int)pmatch.rm_so, str, " ", str + pmatch.rm_eo);
            strncpy(str, tmp, sizeof(tmp) - 1);
            str[sizeof(tmp) - 1] = '\0';
        }
    }

    regfree(&space_regex);
    regfree(&underscore_regex);
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    
    swap_spaces_underscores(test_str);
    
    printf("%s\n", test_str);
    
    return 0;
}