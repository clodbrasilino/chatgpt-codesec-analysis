#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_before_capitals(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t max_output_len = input_len * 2 + 1;
    char *output = (char *)malloc(max_output_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t output_pos = 0;
    size_t search_pos = 0;
    const char *current = input;

    while (search_pos < input_len) {
        ret = regexec(&regex, current, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            strcpy(output + output_pos, current);
            output_pos += strlen(current);
            break;
        } else if (ret != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (matches[0].rm_so > 0) {
            strncpy(output + output_pos, current, matches[0].rm_so);
            output_pos += matches[0].rm_so;
            output[output_pos++] = ' ';
        }

        output[output_pos++] = current[matches[0].rm_so];
        search_pos += matches[0].rm_so + 1;
        current += matches[0].rm_so + 1;
    }

    output[output_pos] = '\0';
    regfree(&regex);
    return output;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "ThisIsATestString",
        "noCapitalsHere",
        "Already Spaced String",
        "MiXeDCase",
        "",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *result = add_spaces_before_capitals(test_strings[i]);
        if (result != NULL) {
            printf("Input: '%s'\nOutput: '%s'\n\n", test_strings[i], result);
            free(result);
        } else {
            printf("Input: '%s'\nOutput: (error)\n\n", test_strings[i]);
        }
    }

    return 0;
}