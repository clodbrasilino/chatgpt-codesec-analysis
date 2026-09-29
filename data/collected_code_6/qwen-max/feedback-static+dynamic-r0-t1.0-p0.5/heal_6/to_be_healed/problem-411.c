#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (!camel_str) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(camel_str, snake_str, len + 1);

    regex_t regex;
    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'matches' undeclared (first use in this function)
     *  use of undeclared identifier 'matches'
     */
    for (int i = 0; regexec(&regex, camel_str + i, 2, matches, 0) == 0; i += matches[0].rm_eo - 1) {
        /* Possible weaknesses found:
         *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
         *  use of undeclared identifier 'matches'
         */
        int match_len = matches[0].rm_eo - matches[1].rm_so - 1;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'matches'
         */
        camel_str[matches[1].rm_so] = toupper((unsigned char)camel_str[matches[1].rm_so + 1]);
        /* Possible weaknesses found:
         *  use of undeclared identifier 'matches'
         */
        memmove(camel_str + matches[1].rm_so + 1, camel_str + matches[1].rm_so + 2, len - (matches[1].rm_so + 1) + 1);
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str[] = {"android_tv", "google_pixel", "apple_watch", "this_is_a_snake_case_string"};
    for (int j = 0; j < 4; j++) {
        char *camel_str = snake_to_camel(snake_str[j]);
        if (camel_str) {
            printf("%s\n", camel_str);
            free(camel_str);
        } else {
            printf("Error converting string.\n");
        }
    }
    return 0;
}