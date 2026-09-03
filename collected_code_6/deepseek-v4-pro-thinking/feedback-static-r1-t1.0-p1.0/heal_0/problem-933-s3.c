#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reg_result = regcomp(&regex, "^[A-Z]", REG_EXTENDED);
    if (reg_result != 0) {
        return NULL;
    }

    size_t length = strlen(input);
    char *output = malloc(length * 2 + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t output_index = 0;
    regmatch_t match;

    for (size_t i = 0; i < length; i++) {
        int is_upper = 0;
        int exec_result = regexec(&regex, input + i, 1, &match, 0);

        if (exec_result == 0) {
            is_upper = 1;
        } else if (exec_result != REG_NOMATCH) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (is_upper) {
            if (i > 0) {
                output[output_index++] = '_';
            }
            output[output_index++] = (char)tolower((unsigned char)input[i]);
        } else {
            output[output_index++] = input[i];
        }
    }

    output[output_index] = '\0';

    regfree(&regex);
    return output;
}

int main(void) {
    const char *camel = "camelCaseString";
    char *snake = camel_to_snake(camel);

    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    }

    return 0;
}