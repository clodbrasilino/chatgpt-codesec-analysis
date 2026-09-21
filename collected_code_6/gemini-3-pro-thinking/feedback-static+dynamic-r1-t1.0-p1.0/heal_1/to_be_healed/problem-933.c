#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t max_len = (strlen(input) * 2) + 1;
    char *result = (char *)calloc(max_len, sizeof(char));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *res_cursor = result;
    regmatch_t pmatch[3];

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = (size_t)pmatch[1].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(res_cursor, cursor, prefix_len);
        res_cursor += prefix_len;
        
        *res_cursor = '_';
        res_cursor++;
        
        cursor += pmatch[2].rm_so;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(res_cursor, cursor);
    regfree(&regex);

    for (char *p = result; *p != '\0'; ++p) {
        *p = (char)tolower((unsigned char)*p);
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake_case",
        "convert123ToSnake",
        "SimpleTest",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; ++i) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", test_cases[i], snake);
            free(snake);
        } else {
            fprintf(stderr, "Failed to convert %s\n", test_cases[i]);
        }
    }

    return 0;
}