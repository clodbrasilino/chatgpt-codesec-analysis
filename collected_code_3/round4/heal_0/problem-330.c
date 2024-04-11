#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_words(char *str) {
    regex_t regex;
    regmatch_t matches[1];
    char *pattern = "\\b\\w{3,5}\\b";
    char *cursor = str;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Failed to compile regex.\n");
        return;
    }

    while (regexec(&regex, cursor, 1, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        char word[6];
        strncpy(word, cursor + start, end - start);
        word[end - start] = '\0';
        printf("%s\n", word);
        cursor += end;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This is a test string with some words of varying lengths.";
    find_words(str);
    return 0;
}