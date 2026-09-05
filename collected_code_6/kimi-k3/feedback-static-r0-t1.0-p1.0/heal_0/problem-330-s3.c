#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_words(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";
    const char *cursor;
    int ret;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = str;
    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), cursor + match.rm_so);
        if (match.rm_eo == 0) {
            cursor++;
        } else {
            cursor += match.rm_eo;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *text = "This is a test string with some three four and five letter words like apple pear fig";
    int result = find_words(text);
    if (result != 0) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }
    return 0;
}