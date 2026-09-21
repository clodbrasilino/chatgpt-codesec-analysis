#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string(const char *str, const char *pattern) {
    regex_t regex;
    regmatch_t pmatch[1];
    int status;
    const char *p = str;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int match_start = pmatch[0].rm_so;
        int match_end = pmatch[0].rm_eo;

        if (match_start > 0) {
            char *token = (char *)malloc((size_t)match_start + 1);
            if (token != NULL) {
                strncpy(token, p, (size_t)match_start);
                token[match_start] = '\0';
                printf("Token: %s\n", token);
                free(token);
            } else {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return;
            }
        }

        p += match_end;
    }

    if (*p != '\0') {
        printf("Token: %s\n", p);
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "apple,orange;banana|grape melon";
    const char *delimiters_pattern = "[,;| ]+";

    split_string(text, delimiters_pattern);

    return 0;
}