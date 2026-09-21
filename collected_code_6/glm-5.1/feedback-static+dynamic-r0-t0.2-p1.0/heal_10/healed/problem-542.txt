#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    
    size_t max_result_len = len + 1;
    char* result = (char*)malloc(max_result_len);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    regmatch_t match;

    while (i < len) {
        ret = regexec(&regex, str + i, 1, &match, 0);
        if (ret == 0) {
            size_t start = i + match.rm_so;
            size_t end = i + match.rm_eo;
            size_t copy_len = start - i;

            if (copy_len > 0) {
                memcpy(result + j, str + i, copy_len);
                j += copy_len;
            }

            if (j < max_result_len) {
                result[j++] = ':';
            }

            i = end;
        } else {
            size_t copy_len = len - i;
            if (copy_len > 0) {
                memcpy(result + j, str + i, copy_len);
                j += copy_len;
            }
            i = len;
        }
    }

    if (j < max_result_len) {
        result[j] = '\0';
    } else {
        result[max_result_len - 1] = '\0';
        j = max_result_len;
    }
    
    regfree(&regex);

    char* resized = realloc(result, j + 1);
    if (resized != NULL) {
        result = resized;
    }

    return result;
}

int main(void) {
    const char* input = "This is a test, with spaces, commas. and dots.";
    char* output = replace_with_colon(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}