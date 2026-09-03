#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *ptr = str, *const end = str + strlen(str);
    
    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) {
        return;
    }

    while (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, end - (ptr + pmatch[0].rm_eo) + 1);
        *ptr = ':';
        ptr += pmatch[0].rm_so + 1;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World. This is a test string.";
    replace_chars(input);
    printf("%s\n", input);
    return 0;
}