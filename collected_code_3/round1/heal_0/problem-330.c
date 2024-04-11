#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_words(char *str) {
    regex_t regex;
    regmatch_t matches[1];
    char *pattern = "\\b\\w{3,5}\\b";
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        printf("Could not compile regex\n");
        return;
    }

    while (!regexec(&regex, str, 1, matches, 0)) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        char word[6];
        strncpy(word, str + start, end - start);
        word[end - start] = '\0';
        printf("%s\n", word);
        str += end;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This is a test string with several words of different lengths.";
    find_words(str);
    return 0;
}