#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  include '<ctype.h>' or provide a declaration of 'toupper'
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t match[2];
    char *camel_str, *p, *result;
    /* Possible weaknesses found:
     *  The scope of the variable 'match_len' can be reduced. [variableScope]
     */
    int len, match_len, i;

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(snake_str);
    camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(camel_str, snake_str);

    p = camel_str;
    while (regexec(&regex, p, 2, match, 0) == 0) {
        match_len = match[1].rm_eo - match[1].rm_so;
        for (i = 0; i < match_len; i++) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
             *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            p[match[1].rm_so + i] = toupper(p[match[1].rm_so + i]);
        }
        p += match[0].rm_eo;
    }

    regfree(&regex);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = realloc(camel_str, strlen(camel_str) + 1);
    if (result == NULL) {
        free(camel_str);
        return NULL;
    }
    return result;
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