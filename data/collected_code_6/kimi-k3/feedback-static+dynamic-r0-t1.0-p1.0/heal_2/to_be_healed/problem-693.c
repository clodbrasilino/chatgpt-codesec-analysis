#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char* remove_multiple_spaces(const char* input) {
    regex_t regex;
    regmatch_t match;
    char* result;
    char* temp;
    size_t result_size;
    size_t input_len;
    size_t pos = 0;
    size_t last_pos = 0;
    size_t result_len = 0;
    int ret;
    
    if (input == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    result_size = input_len + 1;
    
    result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    
    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }
    
    while (pos <= input_len) {
        ret = regexec(&regex, input + pos, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        
        size_t match_start = pos + match.rm_so;
        size_t match_end = pos + match.rm_eo;
        
        size_t segment_len = match_start - last_pos;
        
        if (result_len + segment_len + 1 >= result_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, input + last_pos, segment_len);
        result_len += segment_len;
        result[result_len] = '\0';
        
        if (result_len + 1 >= result_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        
        result[result_len] = ' ';
        result_len++;
        result[result_len] = '\0';
        
        last_pos = match_end;
        pos = match_end;
    }
    
    size_t remaining_len = input_len - last_pos;
    if (result_len + remaining_len >= result_size) {
        regfree(&regex);
        free(result);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + result_len, input + last_pos, remaining_len);
    result_len += remaining_len;
    result[result_len] = '\0';
    
    regfree(&regex);
    
    temp = realloc(result, result_len + 1);
    if (temp != NULL) {
        result = temp;
    }
    
    return result;
}

int main(void) {
    const char* test_string = "This   is    a     test    string   with    multiple     spaces.";
    char* cleaned_string;
    
    printf("Original: %s\n", test_string);
    
    cleaned_string = remove_multiple_spaces(test_string);
    
    if (cleaned_string == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }
    
    printf("Cleaned:  %s\n", cleaned_string);
    
    free(cleaned_string);
    
    return EXIT_SUCCESS;
}