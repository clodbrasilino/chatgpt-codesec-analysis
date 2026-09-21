#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_characters(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[ ,.]+";
    const char replacement[] = ":";
    size_t str_len = strlen(str);
    char *buffer = malloc(str_len + 1);
    if (!buffer) return;

    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        int len = 0;
        while (regexec(&regex, str + len, 1, pmatch, 0) == 0) {
            int match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            for (int i = 0; i <= match_len; i++) {
                buffer[len + i] = replacement[0];
            }
            len += match_len;
            memmove(str + pmatch[0].rm_eo, str + pmatch[0].rm_so, strlen(str + pmatch[0].rm_so) + 1);
            len += pmatch[0].rm_so;
        }
        regfree(&regex);
        buffer[len] = '\0';
        size_t new_len = strlen(str) + strlen(buffer + len);
        if (new_len < str_len) {
            strcat(str, buffer + len);
        }
        free(buffer);
    } else {
        free(buffer);
    }
}

int main() {
    char input[] = "This is a test, to check. the function works properly with spaces, commas, and dots.";
    printf("Original: %s\n", input);
    replace_characters(input);
    printf("Modified: %s\n", input);
    return 0;
}