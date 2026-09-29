#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) {
        return;
    }
    
    char *ptr = str;
    while (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
        const char *end = str + strlen(str);
        size_t len = end - (ptr + pmatch[0].rm_eo);
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, len + 1);
        *ptr = ':';
        ptr += 2;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}