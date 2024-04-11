#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    char *pattern = "\\b\\w{5}\\b";

    regcomp(&regex, pattern, REG_EXTENDED);
    while (regexec(&regex, str, nmatch, pmatch, 0) == 0) {
        char match[6];
        strncpy(match, str + pmatch[0].rm_so, pmatch[0].rm_eo - pmatch[0].rm_so);
        match[5] = '\0';
        printf("%s\n", match);
        str += pmatch[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello world, this is a test string with five char words";
    find_five_char_words(str);
    return 0;
}