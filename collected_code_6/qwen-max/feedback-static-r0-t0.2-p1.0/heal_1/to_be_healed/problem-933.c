#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *output = malloc(strlen(input) * 2 + 1);
    int output_index = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        /* Possible weaknesses found:
         *  Memory leak: output [memleak]
         */
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (int i = 0; i < strlen(input); ++i) {
        if (regexec(&regex, input + i, 2, matches, 0) == 0) {
            output[output_index++] = input[i];
            output[output_index++] = '_';
            i += matches[1].rm_eo - matches[1].rm_so - 1;
        } else {
            output[output_index++] = input[i];
        }
    }

    output[output_index] = '\0';
    regfree(&regex);
    return output;
}

int main() {
    const char *input = "ThisIsCamelCase";
    char *output = camel_to_snake(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error converting string.\n");
    }

    return 0;
}