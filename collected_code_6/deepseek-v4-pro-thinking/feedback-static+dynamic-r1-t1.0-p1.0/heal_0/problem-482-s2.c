#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    int ret;
    const char *pattern = "[A-Z][a-z]+";
    regmatch_t match;
    const char *p = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "regcomp failed: %d\n", ret);
        return;
    }

    while ((ret = regexec(&regex, p, 1, &match, 0)) == 0) {
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), p + match.rm_so);
        p += match.rm_eo;
        if (match.rm_eo == match.rm_so) {
            p++;
        }
    }

    if (ret != REG_NOMATCH) {
        fprintf(stderr, "regexec failed: %d\n", ret);
    }

    regfree(&regex);
}

int main(int argc, char **argv) {
    const char *str = argc > 1 ? argv[1] : "HelloWorld Example Test ABCdef";
    find_sequences(str);
    return 0;
}