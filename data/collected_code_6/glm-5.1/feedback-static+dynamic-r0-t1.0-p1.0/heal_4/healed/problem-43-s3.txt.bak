#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int find_lowercase_underscore(const char *str) {
    regex_t regex;
    int ret;
    regmatch_t matches[1];
    const char *pattern = "[a-z]+_[a-z]+";
    const char *cursor = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        int length = end - start;

        char *match = malloc(length + 1);
        if (match == NULL) {
            regfree(&regex);
            return -1;
        }

        memcpy(match, cursor + start, length);
        match[length] = '\0';

        printf("%s\n", match);
        free(match);

        if (end == 0) {
            break;
        }
        cursor += end;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = find_lowercase_underscore(argv[1]);
    if (result != 0) {
        return 1;
    }

    return 0;
}