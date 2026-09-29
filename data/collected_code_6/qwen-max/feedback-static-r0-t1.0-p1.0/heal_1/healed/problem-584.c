#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_adverbs(const char *sentence) {
    regex_t regex;
    int reti;
    regmatch_t match[1];
    char *str = (char *)sentence;

    const char *pattern = "\\b\\w+ly\\b";
    reti = regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (!regexec(&regex, str, 1, match, 0)) {
        for (int i = 0; i <= match[0].rm_eo - match[0].rm_so; i++) putchar(str[match[0].rm_so + i]);
        printf(" found at position: %d\n", match[0].rm_so);
        str += match[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *sentence = "He quickly and quietly walked away.";
    find_adverbs(sentence);
    return 0;
}