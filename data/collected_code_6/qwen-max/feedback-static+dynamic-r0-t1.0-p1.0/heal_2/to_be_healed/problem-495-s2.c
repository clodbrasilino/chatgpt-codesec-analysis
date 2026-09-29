#include <stdio.h>
#include <string.h>
#include <regex.h>

int remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    int offset = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        return -1;
    }

    while (1) {
        int status = regexec(&regex, str + offset, 1, match, 0);
        if (status == REG_NOMATCH)
            break;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + offset, str + offset + match[0].rm_eo, strlen(str + offset + match[0].rm_so) - (match[0].rm_eo - match[0].rm_so) + 1);
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "TesTIngStrinG";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}