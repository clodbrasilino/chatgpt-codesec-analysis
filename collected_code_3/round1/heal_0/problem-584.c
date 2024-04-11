#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100

void find_adverbs(char* str) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    char* pattern = "\\b\\w+ly\\b"; // simple pattern to match adverbs ending in 'ly'

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("Could not compile regex\n");
        return;
    }

    char* cursor = str;
    while (!regexec(&regex, cursor, MAX_MATCHES, matches, 0)) {
        int offset = matches[0].rm_eo;
        char result[offset + 1];
        strncpy(result, cursor, offset);
        result[offset] = '\0';
        printf("Found adverb: %s at position: %ld\n", result, cursor - str);
        cursor += offset;
    }

    regfree(&regex);
}

int main() {
    char* sentence = "He quickly ran and quietly sat down.";
    find_adverbs(sentence);
    return 0;
}