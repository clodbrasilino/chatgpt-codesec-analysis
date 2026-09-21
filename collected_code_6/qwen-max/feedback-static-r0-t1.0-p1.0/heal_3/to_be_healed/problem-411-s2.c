#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>

char *snake_to_camel(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }
    memset(output, 0, input_len + 1);
    regex_t preg;
    regmatch_t pmatch[2];
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t dst = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (regexec(&preg, &input[i], 2, pmatch, 0) == 0) {
                output[dst++] = toupper((unsigned char)input[i+1]);
                i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
            } else {
                output[dst++] = input[i];
            }
        }
    }
    regfree(&preg);
    return output;
}

int main() {
    const char *snake = "this_is_snake_case";
    char *camel = snake_to_camel(snake);
    if (camel != NULL) {
        printf("Camel case: %s\n", camel);
        free(camel);
    }
    return 0;
}