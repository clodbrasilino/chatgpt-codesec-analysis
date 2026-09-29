#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_words(char *str, size_t max_size) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "([A-Z][^A-Z]*)";
    char replacement[] = " \\1";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[1024] = "";
    /* Possible weaknesses found:
     *  The scope of the variable 'end' can be reduced. [variableScope]
     */
    int rc, start = 0, end;
    
    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE)) {
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'rc' is used in the enclosing expression, the value is never actually read from 'rc' [deadcode.DeadStores]
     */
    while ((rc = regexec(&regex, str + start, 2, matches, 0)) == 0) {
        end = matches[0].rm_so + start;
        size_t len = end - start;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(result) + len < sizeof(result) - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, str + start, len);
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t rep_len = strlen(replacement) - 1;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(result) + rep_len < sizeof(result) - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, replacement, rep_len);
        }
        start = matches[0].rm_eo + start;
    }

    char *remaining = str + start;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(remaining);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t space_left = sizeof(result) - strlen(result) - 1;
    if (space_left > 0 && remaining_len < space_left) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, remaining, remaining_len);
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, result, max_size - 1);
    str[max_size - 1] = '\0';

    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}