#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>

char *snake_to_camel(const char *input) {
    size_t input_len = strlen(input);
    char *output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }
    *output = '\0';
    regex_t preg;
    regmatch_t pmatch[2];
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED | REG_NEWLINE) == 0) {
        int dst = 0;
        for (int i = 0; i < input_len; ++i) {
            if (regexec(&preg, &input[i], 2, pmatch, 0) == 0) {
                if (pmatch[1].rm_so != -1 && pmatch[1].rm_eo != -1 && (size_t)(pmatch[1].rm_so + i) < input_len) {
                    output[dst++] = toupper((unsigned char)input[pmatch[1].rm_so + i]);
                    i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
                } else {
                    output[dst++] = input[i];
                }
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