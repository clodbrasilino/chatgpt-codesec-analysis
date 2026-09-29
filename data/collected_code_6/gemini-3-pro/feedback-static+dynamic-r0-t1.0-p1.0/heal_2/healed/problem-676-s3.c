#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void filter_alphanumeric(const char *input, char *output, size_t out_size) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]+";
    const char *cursor = input;
    size_t out_len = 0;
    
    if (out_size == 0 || input == NULL || output == NULL) {
        return;
    }
    
    output[0] = '\0';
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }
    
    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t len = (size_t)pmatch[0].rm_so;
        if (out_len + len >= out_size) {
            len = out_size - out_len - 1;
        }
        if (len > 0) {
            for (size_t i = 0; i < len; i++) {
                output[out_len + i] = cursor[i];
            }
            out_len += len;
        }
        cursor += pmatch[0].rm_eo;
    }
    
    size_t remaining_len = 0;
    while (cursor[remaining_len] != '\0') {
        remaining_len++;
    }
    
    if (out_len + remaining_len >= out_size) {
        remaining_len = out_size - out_len - 1;
    }
    
    if (remaining_len > 0) {
        for (size_t i = 0; i < remaining_len; i++) {
            output[out_len + i] = cursor[i];
        }
        out_len += remaining_len;
    }
    
    output[out_len] = '\0';
    regfree(&regex);
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output;
    size_t input_len = 0;
    
    while (input[input_len] != '\0') {
        input_len++;
    }
    
    output = malloc(input_len + 1);
    if (output == NULL) {
        return 1;
    }
    
    filter_alphanumeric(input, output, input_len + 1);
    printf("%s\n", output);
    
    free(output);
    return 0;
}