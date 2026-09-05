#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t match;
    int ret;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), cursor + match.rm_so);

        if (match.rm_eo == 0) {
            break;
        }

        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    find_sequences(argv[1]);

    return 0;
}