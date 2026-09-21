#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_regex(const char *str, const char *pattern) {
    regex_t regex;
    regmatch_t pmatch[1];
    int status;
    const char *cursor = str;

    if (str == NULL || pattern == NULL) {
        return;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return;
    }

    while (1) {
        status = regexec(&regex, cursor, 1, pmatch, 0);
        if (status == 0) {
            int len = pmatch[0].rm_so;
            if (len > 0) {
                char *token = strndup(cursor, len);
                if (token != NULL) {
                    printf("%s\n", token);
                    free(token);
                }
            }
            cursor += pmatch[0].rm_eo;
        } else {
            if (*cursor != '\0') {
                printf("%s\n", cursor);
            }
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *str = "apple,orange;banana|grape";
    const char *pattern = "[,;|]";

    split_string_regex(str, pattern);

    return 0;
}