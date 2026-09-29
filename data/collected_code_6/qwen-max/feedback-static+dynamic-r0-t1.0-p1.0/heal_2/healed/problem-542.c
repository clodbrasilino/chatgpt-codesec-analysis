#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void replace_characters(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[ ,.]+";
    const char *replacement = ":";
    size_t str_len = strlen(str);
    char *buffer = (char *)malloc(str_len + 1);

    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        if (regexec(&regex, str, 1, pmatch, 0) != REG_NOMATCH) {
            regfree(&regex);
            int len = 0;

            while (1) {
                for (int i = 0; i <= pmatch[0].rm_eo - pmatch[0].rm_so; i++) {
                    buffer[len + i] = replacement[0];
                }
                len += (pmatch[0].rm_eo - pmatch[0].rm_so);
                memmove(str + pmatch[0].rm_eo, str + pmatch[0].rm_so, str_len + 1 - (pmatch[0].rm_so + (pmatch[0].rm_eo - pmatch[0].rm_so)));
                len += pmatch[0].rm_so;
                regexec(&regex, str + len, 1, pmatch, 0);
                if (pmatch[0].rm_so == -1) break;
                buffer[len] = '\0';
                strncat(str, buffer + len, str_len + 1 - strlen(str));
                memset(buffer, 0, str_len + 1);
            }
        }
        regfree(&regex);
    }
    free(buffer);
}

int main() {
    char input[] = "This is a test, to check. the function works properly with spaces, commas, and dots.";
    printf("Original: %s\n", input);
    replace_characters(input);
    printf("Modified: %s\n", input);
    return 0;
}