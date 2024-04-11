#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_words(char *str) {
    regex_t regex;
    regmatch_t match[1];

    if (regcomp(&regex, "\\b\\w{4,}\\b", REG_EXTENDED) != 0) {
        printf("Failed to compile regex.\n");
        return;
    }

    while (regexec(&regex, str, 1, match, 0) != REG_NOMATCH) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;

        printf("Found: ");
        for (int i = start; i < end; i++) {
            printf("%c", str[i]);
        }
        printf("\n");

        str += end;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This is a test string with some long words.";
    find_words(str);
    return 0;
}