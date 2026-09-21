#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str, size_t len) {
    regex_t regex;
    regmatch_t pmatch[1];
    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) {
        return;
    }
    
    char *ptr = str;
    while (ptr < str + len && regexec(&regex, ptr, 1, pmatch, 0) == 0) {
        const char *end = str + len;
        size_t move_len = end - (ptr + pmatch[0].rm_eo);
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, move_len + 1);
        *ptr = ':';
        ptr += 2;
        len--;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}