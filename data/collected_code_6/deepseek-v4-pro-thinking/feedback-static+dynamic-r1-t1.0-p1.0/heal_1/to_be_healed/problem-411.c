#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char *snake_to_camel(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "_+([a-zA-Z])", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *output = malloc(len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *dest = output;

    while (*cursor != '\0') {
        regmatch_t matches[2];
        int status = regexec(&regex, cursor, 2, matches, 0);

        if (status == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, cursor, remaining + 1);
            dest += remaining;
            break;
        } else if (status != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (matches[0].rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, cursor, (size_t)matches[0].rm_so);
            dest += matches[0].rm_so;
        }

        if (matches[1].rm_so == -1) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        *dest++ = (char)toupper((unsigned char)cursor[matches[1].rm_so]);
        cursor += matches[0].rm_eo;
    }

    *dest = '\0';
    regfree(&regex);
    return output;
}

int main(void)
{
    const char *input = "snake_case_string";
    char *result = snake_to_camel(input);

    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);
    return EXIT_SUCCESS;
}