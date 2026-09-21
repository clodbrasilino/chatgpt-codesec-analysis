#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *ptr = str;
    size_t str_len;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_len = strlen(str);

    while (*ptr && (size_t)(ptr - str) < str_len) {
        if (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
            memmove(ptr + pmatch[0].rm_so, ptr + pmatch[0].rm_eo, str_len - (ptr - str + pmatch[0].rm_eo) + 1);
            str_len -= pmatch[0].rm_eo - pmatch[0].rm_so;
        } else {
            ++ptr;
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World! 123";
    printf("Original: %s\n", str);
    sanitize_string(str);
    printf("Sanitized: %s\n", str);
    return 0;
}