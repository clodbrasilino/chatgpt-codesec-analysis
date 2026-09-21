#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_words(char *str, size_t str_len) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "([A-Z][^A-Z]*)";
    char replacement[] = " \\1";

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  variable-sized object may not be initialized
     *  variable-sized object may not be initialized except with an empty initializer
     */
    char result[str_len] = "";
    int start = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, str + start, 2, matches, 0) == 0) {
        int end = matches[0].rm_so + start;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = (end - start < str_len - 1 - strlen(result)) ? end - start : str_len - 1 - strlen(result);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, str + start, len1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = (sizeof(replacement) - 2 < str_len - 1 - strlen(result)) ? sizeof(replacement) - 2 : str_len - 1 - strlen(result);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, replacement + 1, len2);
        start = matches[0].rm_eo + start;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = (str_len - start - 1 < str_len - 1 - strlen(result)) ? str_len - start - 1 : str_len - 1 - strlen(result);
    /* Possible weaknesses found:
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
     */
    strncat(result, str + start, remaining_len);
    snprintf(str, str_len, "%s", result);

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}