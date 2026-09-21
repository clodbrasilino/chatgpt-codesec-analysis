#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    const char *pattern = "[a-z]+";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    regmatch_t matches[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        int match_start = matches[0].rm_so;
        int match_end = matches[0].rm_eo;
        memmove(str + match_start, str + match_end, str_len - match_end + 1);
        str_len -= match_end - match_start;
    }

    regfree(&regex);
}

int main() {
    char input[] = "HeLlO WoRlD";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}