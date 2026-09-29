#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void replace_chars_with_colon(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti;
    char *ptr = str;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    while ((reti = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
        ptr[pmatch[0].rm_so] = ':';
        ptr += pmatch[0].rm_eo;
    }

    if (reti != REG_NOMATCH) {
        regfree(&regex);
        return;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World. This is a test string!";
    printf("Original: %s\n", input);
    replace_chars_with_colon(input);
    printf("Modified: %s\n", input);
    return 0;
}