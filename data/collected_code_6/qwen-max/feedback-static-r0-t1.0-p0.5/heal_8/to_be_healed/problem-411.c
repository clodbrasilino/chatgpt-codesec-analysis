#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(snake_str);
    char *camel_str = (char *)malloc(str_len + 1);
    if (camel_str == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(camel_str, snake_str, str_len + 1);

    regex_t regex;
    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    regmatch_t matches[2];
    for (size_t i = 0; regexec(&regex, camel_str + i, 2, matches, 0) == 0; i += matches[0].rm_eo - 1) {
        camel_str[matches[1].rm_so - i] = toupper(camel_str[matches[1].rm_so - i + 1]);
        memmove(camel_str + matches[1].rm_so - i, camel_str + matches[1].rm_so - i + 1, str_len - (matches[1].rm_so - i + 1) + 1);
        str_len--;
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);

    if (camel_str != NULL) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        printf("Error converting string.\n");
    }

    return 0;
}