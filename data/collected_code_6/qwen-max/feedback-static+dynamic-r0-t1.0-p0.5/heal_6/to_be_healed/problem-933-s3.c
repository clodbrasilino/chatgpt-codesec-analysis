#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = malloc(input_len * 2 + 1);
    if (output == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(output, input);
    int offset = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED)) {
        free(output);
        return NULL;
    }

    while (regexec(&regex, output + offset, 2, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(output + offset);
        memmove(output + matches[1].rm_so + 1 + offset, output + matches[1].rm_so + offset, len - (matches[1].rm_so + offset) + 1);
        output[matches[1].rm_so + offset] = '_';
        output[matches[1].rm_so + 1 + offset] = tolower((unsigned char)output[matches[1].rm_so + 1 + offset]);
        offset += 1;
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *test_cases[] = {"ThisIsCamelCase", "google_assistant", "chrome_cast", "quad_core"};
    for (int i = 0; i < 4; ++i) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Error converting string.\n");
        }
    }
    return 0;
}