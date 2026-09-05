#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_non_alphanumeric(const char* input) {
    regex_t regex;
    regmatch_t match;
    char* result = NULL;
    size_t result_len = 0;
    size_t result_capacity = 0;
    const char* cursor = input;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result_capacity = strlen(input) + 1;
    result = (char*)malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0) {
            if (result_len + 1 >= result_capacity) {
                size_t new_capacity = result_capacity * 2;
                char* new_result = (char*)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            result[result_len++] = cursor[match.rm_so];
            cursor += match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            break;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "Hello, World! 123 @#$";
    char* cleaned = remove_non_alphanumeric(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}