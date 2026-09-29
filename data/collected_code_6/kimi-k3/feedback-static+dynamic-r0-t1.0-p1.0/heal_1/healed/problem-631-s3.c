#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_whitespace_underscore(const char *input, size_t length) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    char *result = NULL;
    size_t result_idx = 0;
    size_t i = 0;

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[ \t\n\v\f\r_]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (i < length) {
        regmatch_t match;
        ret = regexec(&regex, input + i, 1, &match, 0);
        
        if (ret == 0) {
            size_t match_start = i + match.rm_so;
            size_t match_end = i + match.rm_eo;
            
            while (i < match_start) {
                result[result_idx++] = input[i++];
            }
            
            if (input[match_start] == '_') {
                result[result_idx++] = ' ';
            } else {
                result[result_idx++] = '_';
            }
            
            i = match_end;
        } else if (ret == REG_NOMATCH) {
            while (i < length) {
                result[result_idx++] = input[i++];
            }
        } else {
            regfree(&regex);
            free(result);
            return NULL;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    char test_string[] = "Hello World_This is_a test";
    size_t test_length = sizeof(test_string) - 1;
    char *modified_string = NULL;

    printf("Original: %s\n", test_string);

    modified_string = replace_whitespace_underscore(test_string, test_length);
    if (modified_string == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Modified: %s\n", modified_string);

    free(modified_string);
    return EXIT_SUCCESS;
}