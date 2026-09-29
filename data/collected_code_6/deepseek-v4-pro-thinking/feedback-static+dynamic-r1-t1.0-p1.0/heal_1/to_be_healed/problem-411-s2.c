#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *output = malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }

    regex_t regex;
    int reg_result = regcomp(&regex, "_([[:alnum:]])", REG_EXTENDED);
    if (reg_result != 0) {
        free(output);
        return NULL;
    }

    size_t dst = 0;
    const char *cursor = input;
    regmatch_t matches[2];

    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t prefix = (size_t)matches[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + dst, cursor, prefix);
        dst += prefix;

        unsigned char next = (unsigned char)cursor[matches[1].rm_so];
        output[dst++] = (char)toupper(next);

        cursor += matches[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(output + dst, cursor);
    regfree(&regex);

    return output;
}

int main(void) {
    const char *snake = "hello_world_from_regex";
    char *camel = snake_to_camel(snake);

    if (camel == NULL) {
        return 1;
    }

    printf("%s\n", camel);
    free(camel);

    return 0;
}