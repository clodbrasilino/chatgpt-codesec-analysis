#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 1048576

char* add_spaces_regex(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t length = strnlen(input, MAX_INPUT_LEN);
    if (length == MAX_INPUT_LEN) {
        return NULL;
    }
    
    size_t capacity = length * 2 + 1;
    char* output = malloc(capacity);
    if (output == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[A-Z][a-z0-9]*", REG_EXTENDED);
    if (reti) {
        free(output);
        return NULL;
    }

    regmatch_t matches[1];
    const char* p = input;
    size_t out_index = 0;

    while (1) {
        reti = regexec(&regex, p, 1, matches, 0);
        if (reti == 0) {
            size_t match_len = (size_t)(matches[0].rm_eo - matches[0].rm_so);
            
            if (matches[0].rm_so > 0) {
                if (out_index + matches[0].rm_so >= capacity) {
                    break;
                }
                memcpy(output + out_index, p, matches[0].rm_so);
                out_index += matches[0].rm_so;
            }
            
            if (out_index > 0 && output[out_index - 1] != ' ') {
                if (out_index + 1 >= capacity) {
                    break;
                }
                output[out_index++] = ' ';
            }
            
            if (out_index + match_len >= capacity) {
                break;
            }
            memcpy(output + out_index, p + matches[0].rm_so, match_len);
            out_index += match_len;
            
            p += matches[0].rm_eo;
        } else if (reti == REG_NOMATCH) {
            size_t remaining = strnlen(p, MAX_INPUT_LEN - (size_t)(p - input));
            if (out_index + remaining >= capacity) {
                break;
            }
            memcpy(output + out_index, p, remaining);
            out_index += remaining;
            output[out_index] = '\0';
            break;
        } else {
            regfree(&regex);
            free(output);
            return NULL;
        }
    }

    regfree(&regex);
    return output;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsACFunction";
    char* result = add_spaces_regex(test_str);
    
    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }
    
    return 0;
}