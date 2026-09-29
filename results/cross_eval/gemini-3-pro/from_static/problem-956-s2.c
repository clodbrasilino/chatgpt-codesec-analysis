#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_at_uppercase(const char *input) {
    if (input == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    regmatch_t pmatch[1];
    const char *p = input;

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    while (1) {
        ret = regexec(&regex, p, 1, pmatch, 0);
        if (ret == 0) {
            if (pmatch[0].rm_so == 0) {
                printf("%c", p[0]);
                p++;
                continue;
            }
            int len = pmatch[0].rm_so;
            printf("%.*s ", len, p);
            p += len;
        } else {
            if (*p != '\0') {
                printf("%s", p);
            }
            break;
        }
    }
    printf("\n");
    regfree(&regex);
}

int main(void) {
    const char *test_str = "splitThisStringAtUppercaseLetters";
    split_at_uppercase(test_str);
    return 0;
}