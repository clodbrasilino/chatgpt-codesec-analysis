#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *ptr = str;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    while (ptr && *ptr) {
        if (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
            memmove(ptr, ptr + pmatch[0].rm_eo - pmatch[0].rm_so, strlen(ptr + pmatch[0].rm_eo - pmatch[0].rm_so) + 1);
        } else {
            ptr++;
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