#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_before_capitals(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[1];
    const char* pattern = "[A-Z]";
    
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t max_output_len = input_len * 2 + 1;
    char* output = (char*)malloc(max_output_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t output_pos = 0;
    size_t input_pos = 0;
    int first_char = 1;

    while (input_pos < input_len) {
        const char* current = input + input_pos;
        ret = regexec(&regex, current, 1, matches, 0);
        
        if (ret == 0 && matches[0].rm_so == 0) {
            if (!first_char && output_pos > 0) {
                output[output_pos++] = ' ';
            }
            output[output_pos++] = current[0];
            input_pos++;
            first_char = 0;
        } else {
            output[output_pos++] = current[0];
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