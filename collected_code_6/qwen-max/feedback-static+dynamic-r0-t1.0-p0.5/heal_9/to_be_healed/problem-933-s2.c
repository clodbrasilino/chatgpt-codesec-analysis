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
    char *output = (char *)malloc((input_len * 2 + 1) * sizeof(char));
    if (output == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(output, input);

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    int offset = 0;
    for (int i = 0; i < input_len; i++) {
        if (regexec(&regex, output + i + offset, 2, matches, 0) == 0) {
            memmove(output + i + 1 + offset, output + i + 1 + offset, input_len - (i + 1 - offset) + 1);
            output[i + offset] = '_';
            output[i + offset + 1] = tolower((unsigned char)output[i + offset + 1]);
            offset++;
        }
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *inputs[] = {"ThisIsCamelCase", "google_assistant", "chrome_cast", "quad_core"};
    for (size_t i = 0; i < 4; ++i) {
        char *result = camel_to_snake(inputs[i]);
        if (result) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            printf("Error converting string '%s'.\n", inputs[i]);
        }
    }
    return 0;
}