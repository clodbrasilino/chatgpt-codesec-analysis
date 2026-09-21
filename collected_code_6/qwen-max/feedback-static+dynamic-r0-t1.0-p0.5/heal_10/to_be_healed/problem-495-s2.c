#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[1024] = "";
    regmatch_t pmatch[1];
    int nmatch = 1;
    int pos = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    while (regexec(&regex, str + pos, nmatch, pmatch, 0) == 0) {
        int match_start = pmatch[0].rm_so + pos;
        int match_end = pmatch[0].rm_eo + pos;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_space = 1024 - 1 - strlen(result);
        if (pos > 0 && (match_start - pos) <= remaining_space) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, str + pos, match_start - pos);
        }
        pos = match_end;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    if (pos < length) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_space = 1024 - 1 - strlen(result);
        if (length - pos <= remaining_space) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, str + pos, length - pos);
        }
    }

    snprintf(str, 1024, "%s", result);

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt StRiNg";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}