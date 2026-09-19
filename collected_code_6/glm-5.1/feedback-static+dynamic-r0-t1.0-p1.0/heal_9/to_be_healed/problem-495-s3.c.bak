#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char* cursor = input;

    while (*cursor != '\0') {
        regmatch_t match;
        ret = regexec(&regex, cursor, 1, &match, 0);

        if (ret == 0) {
            if (match.rm_so > 0) {
                memcpy(result + result_idx, cursor, match.rm_so);
                result_idx += match.rm_so;
            }
            cursor += match.rm_eo;
        } else {
            size_t remaining = strlen(cursor);
            memcpy(result + result_idx, cursor, remaining);
            result_idx += remaining;
            break;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);

    char* shrunk_result = (char*)realloc(result, result_idx + 1);
    if (shrunk_result != NULL) {
        return shrunk_result;
    }
    
    return result;
}

int main(void) {
    char* str1 = remove_lowercase_substrings("HelloWorld");
    if (str1 != NULL) {
        printf("%s\n", str1);
        free(str1);
    }

    char* str2 = remove_lowercase_substrings("ABCdefGHIjklMNO");
    if (str2 != NULL) {
        printf("%s\n", str2);
        free(str2);
    }

    char* str3 = remove_lowercase_substrings("1234567890");
    if (str3 != NULL) {
        printf("%s\n", str3);
        free(str3);
    }

    /* Possible weaknesses found:
     *  Assignment 'str4=remove_lowercase_substrings(NULL)', assigned value is 0
     *  Calling function 'remove_lowercase_substrings' returns 0
     *  Variable 'str4' can be declared as pointer to const [constVariablePointer]
     */
    char* str4 = remove_lowercase_substrings(NULL);
    /* Possible weaknesses found:
     *  Condition 'str4==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'str4==NULL' is always true
     */
    if (str4 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}