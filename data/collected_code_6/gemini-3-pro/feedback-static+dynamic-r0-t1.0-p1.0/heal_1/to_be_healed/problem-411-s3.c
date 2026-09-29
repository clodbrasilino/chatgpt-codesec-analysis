#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char* str_copy = malloc(len + 1);
    char* result = malloc(len + 1);

    if (str_copy == NULL || result == NULL) {
        free(str_copy);
        free(result);
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str_copy, snake_str);

    regmatch_t pmatch[2];
    char* p = str_copy;
    char* dest = result;

    while (regexec(&regex, p, 2, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(dest, p, match_len);
        dest += match_len;

        *dest = toupper((unsigned char)p[pmatch[1].rm_so]);
        dest++;

        p += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dest, p);

    free(str_copy);
    regfree(&regex);

    return result;
}

int main() {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    }

    return 0;
}