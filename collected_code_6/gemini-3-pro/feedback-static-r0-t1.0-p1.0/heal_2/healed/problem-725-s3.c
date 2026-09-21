#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_quoted_values(const char *input) {
    regex_t regex;
    regmatch_t pmatch[2];
    const char *pattern = "\"([^\"]*)\"";
    const char *p = input;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    while (regexec(&regex, p, 2, pmatch, 0) == 0) {
        if (pmatch[1].rm_so != -1 && pmatch[1].rm_eo >= pmatch[1].rm_so) {
            size_t len = (size_t)(pmatch[1].rm_eo - pmatch[1].rm_so);
            char *match = malloc(len + 1);
            if (match == NULL) {
                regfree(&regex);
                return;
            }
            
            snprintf(match, len + 1, "%.*s", (int)len, p + pmatch[1].rm_so);
            
            printf("%s\n", match);
            free(match);
        }
        p += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *input = "Here is \"first_value\" and \"second_value\".";
    extract_quoted_values(input);
    return 0;
}