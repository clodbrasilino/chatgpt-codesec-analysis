#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (!camel_str) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(camel_str, snake_str);

    regex_t regex;
    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    regmatch_t matches[2];
    while (regexec(&regex, camel_str, 2, matches, 0) == 0) {
        int match_start = matches[1].rm_so + 1;
        camel_str[match_start] = toupper((unsigned char)camel_str[match_start]);
        memmove(camel_str + match_start - 1, camel_str + match_start, len - match_start + 1);
        camel_str[len - 1] = '\0';
        len--;
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