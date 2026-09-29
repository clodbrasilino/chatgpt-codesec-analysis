#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char pattern[] = "([A-Z][^A-Z]*)";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *result = malloc((str_len + 1) * 2);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    result[0] = '\0';

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        free(result);
        exit(1);
    }

    size_t result_len = 0;
    while (regexec(&regex, str, 1, match, 0) == 0) {
        size_t len = match[0].rm_eo - match[0].rm_so;
        if (result_len + len + 2 <= (str_len + 1) * 2) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, str + match[0].rm_so, len);
            result_len += len;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", 1);
            result_len++;
        }
        str += match[0].rm_eo;
    }

    snprintf(str, (str_len + 1) * 2, "%s", result);

    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(input);
    printf("%s\n", input);
    return 0;
}