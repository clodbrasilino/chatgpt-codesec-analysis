#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  */

char* snake_to_camel(const char* snake_str) {
    if (!snake_str) return NULL;

    regex_t regex;
    int reti = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (!camel_str) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[2];
    const char* cursor = snake_str;
    char* out_cursor = camel_str;

    while (regexec(&regex, cursor, 2, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(out_cursor, cursor, prefix_len);
        out_cursor += prefix_len;

        *out_cursor = toupper((unsigned char)cursor[pmatch[1].rm_so]);
        out_cursor++;

        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out_cursor, cursor);

    regfree(&regex);
    return camel_str;
}

int main(void) {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel) {
        printf("%s\n", camel);
        free(camel);
    } else {
        fprintf(stderr, "Conversion failed.\n");
    }

    return 0;
}