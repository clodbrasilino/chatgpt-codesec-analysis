#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_before_capitals(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, 4096);
    if (input_len == 0) {
        char* output = (char*)malloc(1);
        if (output != NULL) {
            output[0] = '\0';
        }
        return output;
    }

    regex_t regex;
    regmatch_t matches[1];
    const char* pattern = "[A-Z]";
    
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_output_len = input_len * 2 + 1;
    if (max_output_len < input_len) {
        regfree(&regex);
        return NULL;
    }

    char* output = (char*)malloc(max_output_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t output_pos = 0;
    size_t input_pos = 0;
    int first_char = 1;

    /* Possible weaknesses found:
     *  Assuming that condition 'output_pos<max_output_len-1' is not redundant
     */
    while (input_pos < input_len && output_pos < max_output_len - 1) {
        const char* current = input + input_pos;
        ret = regexec(&regex, current, 1, matches, 0);
        
        if (ret == 0 && matches[0].rm_so == 0) {
            /* Possible weaknesses found:
             *  Condition 'output_pos<max_output_len-1' is always true
             *  Condition 'output_pos<max_output_len-1' is always true [knownConditionTrueFalse]
             */
            if (!first_char && output_pos > 0 && output_pos < max_output_len - 1) {
                output[output_pos++] = ' ';
            }
            if (output_pos < max_output_len - 1) {
                output[output_pos++] = current[0];
            }
            input_pos++;
            first_char = 0;
        } else {
            /* Possible weaknesses found:
             *  Condition 'output_pos<max_output_len-1' is always true
             *  Condition 'output_pos<max_output_len-1' is always true [knownConditionTrueFalse]
             */
            if (output_pos < max_output_len - 1) {
                output[output_pos++] = current[0];
            }
            input_pos++;
            first_char = 0;
        }
    }

    output[output_pos] = '\0';
    regfree(&regex);
    return output;
}

int main(void) {
    const char* test_strings[] = {
        "HelloWorld",
        "ThisIsATest",
        "already spaced String",
        "ALL CAPS",
        "lowercase",
        "MixedCaseWithNumbers123",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char* result = add_spaces_before_capitals(test_strings[i]);
        if (result != NULL) {
            printf("Input: %s\nOutput: %s\n\n", test_strings[i], result);
            free(result);
        } else {
            printf("Error processing: %s\n\n", test_strings[i]);
        }
    }

    return 0;
}