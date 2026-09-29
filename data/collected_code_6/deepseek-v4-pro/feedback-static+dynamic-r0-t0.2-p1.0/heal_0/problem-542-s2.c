#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void replace_chars_with_colon(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[ ,.]";
    size_t input_len = strlen(input);
    size_t output_pos = 0;
    size_t input_pos = 0;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        if (output_size > 0) {
            output[0] = '\0';
        }
        return;
    }
    
    while (input_pos < input_len && output_pos < output_size - 1) {
        if (regexec(&regex, input + input_pos, 1, &match, 0) == 0) {
            if (match.rm_so == 0) {
                output[output_pos++] = ':';
                input_pos++;
            } else {
                size_t copy_len = match.rm_so;
                if (copy_len > output_size - output_pos - 1) {
                    copy_len = output_size - output_pos - 1;
                }
                memcpy(output + output_pos, input + input_pos, copy_len);
                output_pos += copy_len;
                input_pos += match.rm_so;
            }
        } else {
            size_t remaining = input_len - input_pos;
            if (remaining > output_size - output_pos - 1) {
                remaining = output_size - output_pos - 1;
            }
            memcpy(output + output_pos, input + input_pos, remaining);
            output_pos += remaining;
            break;
        }
    }
    
    output[output_pos] = '\0';
    regfree(&regex);
}

int main(void) {
    const char *test_str = "Hello, world. This is a test";
    char result[256];
    
    replace_chars_with_colon(test_str, result, sizeof(result));
    printf("Original: %s\n", test_str);
    printf("Modified: %s\n", result);
    
    return 0;
}