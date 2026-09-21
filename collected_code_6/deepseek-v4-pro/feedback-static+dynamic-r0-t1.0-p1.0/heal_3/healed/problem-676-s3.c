#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t output_index = 0;
    size_t input_len;
    char *output = NULL;
    int ret;

    if (!input) {
        return NULL;
    }

    input_len = strnlen(input, 4096);
    if (input_len == 4096 && input[4095] != '\0') {
        return NULL;
    }

    output = (char *)malloc(input_len + 1);
    if (!output) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:alnum:]]", REG_EXTENDED);
    if (ret) {
        free(output);
        return NULL;
    }

    cursor = input;
    while (*cursor && regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }
        output[output_index++] = cursor[match.rm_so];
        cursor += match.rm_so + 1;
    }

    output[output_index] = '\0';
    regfree(&regex);
    return output;
}

int main(void) {
    const char *input = "Hello, World! 123 ...";
    char *output = remove_non_alphanumeric(input);
    
    if (output) {
        printf("Input: %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    } else {
        printf("Error: Memory allocation failed or invalid input\n");
    }

    return 0;
}