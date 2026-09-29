#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    int input_len = strlen(input);
    char *output = malloc(input_len * 2 + 1);
    if (output == NULL) return NULL;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    int output_index = 0;
    for (int i = 0; i < input_len; ++i) {
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