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

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        printf("%.*s\n", match.rm_eo - match.rm_so, cursor + match.rm_so);
        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    find_sequences(argv[1]);
    return 0;
}