#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    size_t out_pos = 0;
    const char *cursor;
    int result;

    if (output_size == 0) {
        return;
    }

    if (output == NULL) {
        return;
    }

    if (input == NULL) {
        output[0] = '\0';
        return;
    }

    result = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (result != 0) {
        output[0] = '\0';
        return;
    }

    cursor = input;

    while (out_pos + 1 < output_size) {
        result = regexec(&regex, cursor, 1, &match, 0);
        if (result == REG_NOMATCH) {
            size_t remaining_len = strlen(cursor);
            size_t space_left = output_size - out_pos - 1;
            
            if (remaining_len > space_left) {
                remaining_len = space_left;
            }
            
            if (remaining_len > 0) {
                memcpy(output + out_pos, cursor, remaining_len);
                out_pos += remaining_len;
            }
            break;
        } else if (result == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                size_t space_left = output_size - out_pos - 1;
                
                if (copy_len > space_left) {
                    copy_len = space_left;
                }
                
                if (copy_len > 0) {
                    memcpy(output + out_pos, cursor, copy_len);
                    out_pos += copy_len;
                }
            }
            cursor += match.rm_eo;
            if (*cursor == '\0') {
                break;
            }
        } else {
            size_t remaining_len = strlen(cursor);
            size_t space_left = output_size - out_pos - 1;
            
            if (remaining_len > space_left) {
                remaining_len = space_left;
            }
            
            if (remaining_len > 0) {
                memcpy(output + out_pos, cursor, remaining_len);
                out_pos += remaining_len;
            }
            break;
        }
    }

    if (out_pos < output_size) {
        output[out_pos] = '\0';
    } else {
        output[output_size - 1] = '\0';
    }
    regfree(&regex);
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "abcXYZdef",
        "ABC123low456",
        "test",
        "UPPERlowerUPPER",
        "A1b2C3d4",
        "",
        "alllowercase"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    char *result_buffer = malloc(256);
    if (result_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < num_tests; i++) {
        size_t buffer_size = 256;
        remove_lowercase_substrings(test_strings[i], result_buffer, buffer_size);
        printf("Input: '%s' -> Output: '%s'\n", test_strings[i], result_buffer);
    }

    free(result_buffer);
    return 0;
}