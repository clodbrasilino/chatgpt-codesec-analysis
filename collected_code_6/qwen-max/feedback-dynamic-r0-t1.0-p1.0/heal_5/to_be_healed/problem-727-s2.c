#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *src, *dst;
    int rc;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    src = dst = str;
    /* Possible weaknesses found:
     * ASan: SEGV
     */
    while (*src) {
        if ((rc = regexec(&regex, src, 1, pmatch, 0)) == 0 && pmatch[0].rm_so == 0) {
            src += pmatch[0].rm_eo;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World! 123";
    printf("Original: %s\n", str);
    sanitize_string(str);
    printf("Sanitized: %s\n", str);
    return 0;
}