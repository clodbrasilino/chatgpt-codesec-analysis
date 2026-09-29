#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char* cursor = str;

    while (*cursor != '\0') {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            for (int i = 0; i < match.rm_so; ++i) {
                result[result_idx++] = cursor[i];
            }
            cursor += match.rm_eo;
        } else {
            while (*cursor != '\0') {
                result[result_idx++] = *cursor++;
            }
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);

    char* shrunk = (char*)realloc(result, result_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
    
    return result;
}

int main(void) {
    const char* input = "Hello World 123 test CASE";
    char* output = remove_lowercase_substrings(input);
    
    if (output != NULL) {
        printf("Input:  %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to process string.\n");
        return 1;
    }
    
    return 0;
}