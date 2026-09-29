#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GoogleDart', got <no output>
  *  test case 0 failed: expected 'GoogleFlutter', got <no output>
  *  test case 2 failed: expected 'iOSSwift', got <no output>
  */

char* remove_whitespaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]", 0);
    if (reti != 0) {
        return NULL;
    }
    
    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }
    
    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    size_t result_index = 0;
    size_t result_size = input_len + 1;
    regmatch_t match;
    const char* cursor = input;
    
    while (*cursor != '\0' && regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (result_index + copy_len < result_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_index, cursor, copy_len);
                result_index += copy_len;
            }
        }
        cursor += match.rm_eo;
        if (match.rm_eo == 0) {
            if (result_index < result_size - 1) {
                result[result_index++] = *cursor;
            }
            if (*cursor != '\0') {
                cursor++;
            }
        }
    }
    
    if (*cursor != '\0') {
        size_t remaining = strnlen(cursor, result_size - result_index);
        if (remaining > 0 && result_index + remaining < result_size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, remaining);
            result_index += remaining;
        }
    }
    
    if (result_index < result_size) {
        result[result_index] = '\0';
    } else {
        result[result_size - 1] = '\0';
    }
    
    regfree(&regex);
    return result;
}

int main() {
    const char* test_string = "Hello World\tfrom\nC programming";
    char* cleaned = remove_whitespaces(test_string);
    
    if (cleaned != NULL) {
        printf("Original: '%s'\n", test_string);
        printf("Cleaned: '%s'\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }
    
    return 0;
}