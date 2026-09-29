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
    char *output = strdup(input);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(output);

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        if (regexec(&regex, output + i, 2, matches, 0) == 0) {
            memmove(output + i + 1 + matches[1].rm_so, output + i + matches[1].rm_so, len - (i + matches[1].rm_so) + 1);
            output[i + matches[1].rm_so] = '_';
            output[i + matches[1].rm_so + 1] = tolower((unsigned char)output[i + matches[1].rm_so + 1]);
            len++;
            i += matches[1].rm_so;
        }
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *input = "ThisIsCamelCase";
    char *result = camel_to_snake(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error converting string.\n");
    }
    return 0;
}