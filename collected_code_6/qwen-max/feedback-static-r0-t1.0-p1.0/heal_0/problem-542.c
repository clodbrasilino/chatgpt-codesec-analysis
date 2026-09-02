#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_characters(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[ ,.]+";
    char replacement[] = ":";
    char buffer[1024];

    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        if (regexec(&regex, str, 1, pmatch, 0) != REG_NOMATCH) {
            regfree(&regex);
            int len = 0;
            regmatch_t *pm;

            while (1) {
                pm = pmatch;
                for (int i = 0; i <= pm[0].rm_eo - pm[0].rm_so; i++) {
                    buffer[len + i] = replacement[0];
                }
                len += (pm[0].rm_eo - pm[0].rm_so);
                memmove(str + pm[0].rm_eo, str + pm[0].rm_so, strlen(str) + 1 - (pm[0].rm_so + (pm[0].rm_eo - pm[0].rm_so)));
                len += pm[0].rm_so;
                regexec(&regex, str + len, 1, pmatch, 0);
                if (pmatch[0].rm_so == -1) break;
                buffer[len] = '\0';
                strcat(str, buffer + len);
                memset(buffer, 0, 1024);
            }
        }
        regfree(&regex);
    }
}

int main() {
    char input[] = "This is a test, to check. the function works properly with spaces, commas, and dots.";
    printf("Original: %s\n", input);
    replace_characters(input);
    printf("Modified: %s\n", input);
    return 0;
}