#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_at_uppercase(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (reti) {
        return;
    }

    regmatch_t pmatch[1];
    const char *p = str;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        if (pmatch[0].rm_so > 0) {
            printf("%.*s ", (int)pmatch[0].rm_so, p);
        }
        p += pmatch[0].rm_so;
        
        int next_match = 1;
        while (p[next_match] != '\0' && regexec(&regex, p + next_match, 1, pmatch, 0) != 0) {
            next_match++;
        }
        
        printf("%.*s ", next_match, p);
        p += next_match;
    }

    if (*p != '\0') {
        printf("%s", p);
    }
    printf("\n");

    regfree(&regex);
}

int main(void) {
    const char *test_str = "SplitThisStringAtUppercaseLetters";
    split_at_uppercase(test_str);
    return 0;
}