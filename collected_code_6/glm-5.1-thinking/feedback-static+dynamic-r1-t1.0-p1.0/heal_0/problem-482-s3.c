#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    regmatch_t match;
    const char *p = str;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }

        printf("%.*s\n", match.rm_eo - match.rm_so, p + match.rm_so);

        if (match.rm_eo == match.rm_so) {
            p += 1;
        } else {
            p += match.rm_eo;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Hello World abc DEF Ghi JkL Mno pqr StU VwX yz";
    find_sequences(text);
    return 0;
}