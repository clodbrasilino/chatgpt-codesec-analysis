#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void search_literal_in_string(const char *target, const char *pattern) {
    if (target == NULL || pattern == NULL) {
        printf("Error: Invalid input strings.\n");
        return;
    }

    regex_t regex;
    int ret;
    regmatch_t matches[1];

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        printf("Error compiling regex.\n");
        return;
    }

    const char *p = target;
    int offset = 0;

    while (1) {
        ret = regexec(&regex, p, 1, matches, 0);
        if (ret == 0) {
            printf("Pattern found at offset: %d\n", offset + matches[0].rm_so);
            offset += matches[0].rm_eo;
            p += matches[0].rm_eo;
        } else if (ret == REG_NOMATCH) {
            break;
        } else {
            printf("Error executing regex.\n");
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *target_string = "This is a test string to test the regex test functionality.";
    const char *pattern_string = "test";

    search_literal_in_string(target_string, pattern_string);

    return 0;
}