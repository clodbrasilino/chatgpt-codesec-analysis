#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* add_spaces_before_capitals(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX && input[SIZE_MAX] != '\0') {
        return NULL;
    }

    if (input_len == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    if (input_len > SIZE_MAX / 2) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t result_capacity = input_len * 2 + 1;
    char* result = (char*)malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    const char* cursor = input;
    regmatch_t match;

    while (*cursor != '\0') {
        size_t cursor_offset = (size_t)(cursor - input);
        if (cursor_offset > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (regexec(&regex, cursor, 1, &match, 0) == 0) {
            if (match.rm_so == 0 && cursor != input) {
                if (result_index >= result_capacity) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result[result_index] = ' ';
                result_index++;
            }

            size_t copy_len = (match.rm_so == 0) ? 1 : (size_t)match.rm_so;
            
            if (copy_len > input_len - cursor_offset) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            if (result_index + copy_len >= result_capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            /* Possible weaknesses found:
             *  Invalid test for overflow 'result+result_index<result'; pointer overflow is undefined behavior. Some mainstream compilers remove such overflow tests when optimising the code and assume it's always false. [invalidTestForOverflow]
             */
            if (result + result_index < result || 
                cursor < input || 
                result + result_index + copy_len > result + result_capacity ||
                cursor + copy_len > input + input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, copy_len);
            result_index += copy_len;
            cursor += copy_len;
        } else {
            size_t remaining = input_len - cursor_offset;
            if (remaining == 0) {
                break;
            }

            if (result_index + remaining >= result_capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            /* Possible weaknesses found:
             *  Invalid test for overflow 'result+result_index<result'; pointer overflow is undefined behavior. Some mainstream compilers remove such overflow tests when optimising the code and assume it's always false. [invalidTestForOverflow]
             */
            if (result + result_index < result || 
                cursor < input || 
                result + result_index + remaining > result + result_capacity ||
                cursor + remaining > input + input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, remaining);
            result_index += remaining;
            break;
        }
    }

    if (result_index >= result_capacity) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[result_index] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsATest";
    char* result = add_spaces_before_capitals(test_str);
    
    if (result != NULL) {
        printf("Input: %s\n", test_str);
        printf("Output: %s\n", result);
        free(result);
    } else {
        printf("Error processing string\n");
    }
    
    return 0;
}