#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void replace_characters(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[ ,.]+";
    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        while (regexec(&regex, str, 1, pmatch, 0) == 0) {
            int match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(str + pmatch[0].rm_so + 1, str + pmatch[0].rm_eo, strlen(str + pmatch[0].rm_eo) + 1);
            str[pmatch[0].rm_so] = ':';
            str = strchr(str, '\0') - match_len + 1; // Update the end of the string
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