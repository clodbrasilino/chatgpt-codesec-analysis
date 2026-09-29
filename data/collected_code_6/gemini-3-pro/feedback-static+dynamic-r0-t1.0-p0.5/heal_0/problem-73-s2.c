#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_regex(const char *str, const char *pattern) {
    regex_t regex;
    regmatch_t pmatch[1];
    int status;
    const char *p = str;

    if (str == NULL || pattern == NULL) {
        return;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return;
    }

    while (1) {
        status = regexec(&regex, p, 1, pmatch, 0);
        if (status == 0) {
            int len = pmatch[0].rm_so;
            if (len > 0) {
                char *token = (char *)malloc(len + 1);
                if (token != NULL) {
                    strncpy(token, p, len);
                    token[len] = '\0';
                    printf("%s\n", token);
                    free(token);
                }
            }
            p += pmatch[0].rm_eo;
        } else {
            if (*p != '\0') {
                printf("%s\n", p);
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