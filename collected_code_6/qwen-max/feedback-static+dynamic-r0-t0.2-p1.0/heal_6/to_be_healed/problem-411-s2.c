#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got android_Tv
  *  test case 2 failed: expected 'AppleWatch', got apple_Watch
  *  test case 1 failed: expected 'GooglePixel', got google_Pixel
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t match[2];

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(camel_str, snake_str, len + 1);

    char *p = camel_str;
    while (regexec(&regex, p, 2, match, 0) == 0) {
        int match_len = match[1].rm_eo - match[1].rm_so;
        for (int i = 0; i < match_len; i++) {
            p[match[1].rm_so + i] = toupper(p[match[1].rm_so + i]);
        }
        p += match[0].rm_eo;
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
        printf("Conversion failed.\n");
    }

    return 0;
}