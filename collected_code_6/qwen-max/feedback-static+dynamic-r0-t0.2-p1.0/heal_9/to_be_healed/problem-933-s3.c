#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL || *input == '\0') {
        return NULL;
    }
    regex_t regex;
    regmatch_t matches[2];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = malloc(input_len * 2 + 1);
    if (output == NULL) {
        return NULL;
    }
    int output_index = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    for (int i = 0; i < input_len; ++i) {
        size_t remaining = input_len - i;
        if (regexec(&regex, input + i, 2, matches, 0) == 0) {
            output[output_index++] = tolower((unsigned char)input[i]);
            output[output_index++] = '_';
            i += matches[1].rm_eo - matches[1].rm_so;
        } else if (remaining > 0) {
            output[output_index++] = tolower((unsigned char)input[i]);
        }
    }

    output[output_index] = '\0';
    regfree(&regex);
    return output;
}

int main() {
    const char *inputs[] = {"ThisIsCamelCase", "google_assistant", "chrome_cast", "quad_core"};
    for (size_t i = 0; i < 4; ++i) {
        const char *input = inputs[i];
        char *result = camel_to_snake(input);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("Error converting string.\n");
        }
    }
    return 0;
}