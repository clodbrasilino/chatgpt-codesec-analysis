#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str, size_t str_len) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256] = {0};

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) return;

    for (size_t i = 0; ; i++) {
        int rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH || pmatch[0].rm_so == -1) break;

        size_t len = pmatch[0].rm_so;

        if (len + 1 + (str_len - (i + pmatch[0].rm_eo)) >= sizeof(buffer)) continue;

        snprintf(buffer, sizeof(buffer), "%.*s:%.*s", (int)len, str + i, (int)(str_len - (i + pmatch[0].rm_eo)), str + i + pmatch[0].rm_eo);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t new_len = strlen(buffer);

        memmove(str + i + new_len, str + i + pmatch[0].rm_eo, str_len - (i + pmatch[0].rm_eo));
        memmove(str + i, buffer, new_len + 1);

        i += new_len;
        if (pmatch[0].rm_so == 0) i++;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}