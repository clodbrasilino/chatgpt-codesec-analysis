#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    char *output = malloc(strlen(input) * 2 + 1);
    if (output == NULL) {
        return NULL;
    }
    int output_index = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

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
    char *result = camel_to_snake(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error converting string.\n");
    }
    return 0;
}