#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_words(char *str) {
    regex_t regex;
    regmatch_t matches[1];
    char *pattern = "\\b\\w{3,5}\\b";
    char *cursor = str;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("Could not compile regex\n");
        return;
    }

    while (!regexec(&regex, cursor, 1, matches, 0)) {
        int offset = matches[0].rm_eo;
        char result[6];
        strncpy(result, cursor, offset);
        result[offset] = '\0';
        printf("%s\n", result);
        cursor += offset;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This is a test string with some words of varying lengths.";
    find_words(str);
    return 0;
}