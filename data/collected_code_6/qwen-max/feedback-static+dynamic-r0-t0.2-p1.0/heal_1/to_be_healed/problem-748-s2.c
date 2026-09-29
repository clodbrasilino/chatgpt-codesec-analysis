#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256] = "";
    /* Possible weaknesses found:
     *  Unused variable: rc [unusedVariable]
     */
    int rc;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (regexec(&regex, str, 1, match, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, str + match[0].rm_so, match[0].rm_eo - match[0].rm_so);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncat(result, " ", 1);
        str += match[0].rm_eo;
    }
    /* Possible weaknesses found:
     * ASan: stack-buffer-overflow
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);

    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(input);
    printf("%s\n", input);
    return 0;
}