#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

char* camel_to_snake(const char *camel) {
    regex_t regex;
    regmatch_t matches[2];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel);
    char *snake = (char *)malloc(len * 2 + 1);
    if (!snake) return NULL;
    snake[0] = '\0';

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(snake);
        return NULL;
    }

    const char *p = camel;
    size_t pos = 0;
    while (*p) {
        if (regexec(&regex, p, 2, matches, 0) == 0) {
            size_t match_len = matches[1].rm_eo - matches[1].rm_so;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(snake + pos, p, match_len);
            pos += match_len;
            snake[pos++] = '_';
            p += matches[1].rm_eo;
        } else {
            snake[pos++] = *p;
            p++;
        }
    }
    snake[pos] = '\0';

    regfree(&regex);
    return snake;
}

int main() {
    const char *camel = "ThisIsCamelCase";
    char *snake = camel_to_snake(camel);
    if (snake) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Error converting to snake case.\n");
    }
    return 0;
}