#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_words(char *str) {
    regex_t regex;
    regmatch_t match[2];
    char *pattern = "\\b\\w{4,}\\b";
    regcomp(&regex, pattern, REG_EXTENDED);
    while (regexec(&regex, str, 2, match, 0) == 0) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;
        char word[end - start + 1];
        strncpy(word, str + start, end - start);
        word[end - start] = '\0';
        printf("%s\n", word);
        str += end;
    }
    regfree(&regex);
}

int main() {
    char str[] = "This is a test string with some long words.";
    find_words(str);
    return 0;
}