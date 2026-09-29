#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void swap_spaces_underscores(char *str) {
    regex_t space_regex, underscore_regex;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *tmp = (char *)malloc((str_len + 1) * sizeof(char));
    if (!tmp) return;

    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        free(tmp);
        return;
    }

    int space_found = 0;
    int underscore_found = 0;

    if (regexec(&space_regex, str, 0, NULL, 0) == 0) {
        regmatch_t match;
        while (regexec(&space_regex, str, 1, &match, 0) == 0) {
            snprintf(tmp, str_len + 1, "%.*s_%*s", (int)match.rm_so, str, (int)(str_len - match.rm_eo), str + match.rm_eo);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(str, tmp, str_len + 1);
            str += match.rm_so + 1;
            str[-1] = '_';
            space_found = 1;
        }
    }
    str -= str_len;

    if (regexec(&underscore_regex, str, 0, NULL, 0) == 0) {
        regmatch_t match;
        while (regexec(&underscore_regex, str, 1, &match, 0) == 0) {
            snprintf(tmp, str_len + 1, "%.*s %*s", (int)match.rm_so, str, (int)(str_len - match.rm_eo), str + match.rm_eo);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(str, tmp, str_len + 1);
            str += match.rm_so + 1;
            str[-1] = ' ';
            underscore_found = 1;
        }
    }
    str -= str_len;

    free(tmp);
    regfree(&space_regex);
    regfree(&underscore_regex);

    if (space_found || underscore_found) {
        swap_spaces_underscores(str);
    }
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    swap_spaces_underscores(test_str);
    printf("%s\n", test_str);
    return 0;
}