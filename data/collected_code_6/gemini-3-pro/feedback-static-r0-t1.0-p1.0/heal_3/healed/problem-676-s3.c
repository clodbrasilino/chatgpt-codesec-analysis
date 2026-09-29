#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void filter_alphanumeric(const char *input, char *output, size_t out_size) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]+";
    const char *cursor = input;
    char *out_cursor = output;
    size_t remaining = out_size;

    if (input == NULL || output == NULL || out_size == 0) {
        if (output != NULL && out_size > 0) {
            output[0] = '\0';
        }
        return;
    }

    output[0] = '\0';

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_so;
        
        if (len >= remaining) {
            len = remaining - 1;
        }
        
        if (len > 0) {
            for (size_t i = 0; i < len; i++) {
                out_cursor[i] = cursor[i];
            }
            out_cursor += len;
            remaining -= len;
        }
        
        cursor += pmatch[0].rm_eo;
    }

    size_t end_len = 0;
    while (cursor[end_len] != '\0') {
        end_len++;
    }

    if (end_len >= remaining) {
        end_len = remaining - 1;
    }
    
    if (end_len > 0) {
        for (size_t i = 0; i < end_len; i++) {
            out_cursor[i] = cursor[i];
        }
        out_cursor += end_len;
    }
    
    *out_cursor = '\0';
    
    regfree(&regex);
}

int main(void) {
    const char input[] = "Hello, World! 123 @#$";
    char *output;
    size_t input_size;

    input_size = sizeof(input);
    
    output = malloc(input_size);
    if (output == NULL) {
        return 1;
    }

    filter_alphanumeric(input, output, input_size);
    printf("%s\n", output);

    free(output);
    return 0;
}