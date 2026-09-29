#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_adverbs(char *sentence) {
    regex_t regex;
    regmatch_t match;
    int start = 0;
    int result;

    result = regcomp(&regex, "\\b\\w+ly\\b", REG_EXTENDED);
    if (result) {
        printf("Could not compile regex\n");
        return;
    }

    while (!regexec(&regex, sentence + start, 1, &match, 0)) {
        printf("Found adverb: %.*s at position: %d\n", 
               (int)(match.rm_eo - match.rm_so), 
               sentence + start + match.rm_so, 
               start + match.rm_so);
        start += match.rm_eo;
    }

    regfree(&regex);
}

int main() {
    char sentence[] = "He quickly ran home.";
    find_adverbs(sentence);
    return 0;
}