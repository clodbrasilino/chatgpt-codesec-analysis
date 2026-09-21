#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_multiple_spaces(const char* input) {
    regex_t regex;
    regmatch_t match;
    char* result;
    char* temp;
    size_t result_size;
    size_t input_len;
    size_t pos = 0;
    size_t last_pos = 0;
    size_t current_len = 0;
    int ret;
    
    if (input == NULL) {
        return NULL;
    }
    
    input_len = strnlen(input, 1024 * 1024);
    if (input_len == 1024 * 1024 && input[input_len] != '\0') {
        return NULL;
    }
    
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
        
        /* Possible weaknesses found:
         *  Assuming that condition 'current_len+segment_len+2>result_size' is not redundant
         */
        if (current_len + segment_len + 2 > result_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        
        if (segment_len > 0) {
            /* Possible weaknesses found:
             *  Condition 'current_len+segment_len>=result_size' is always false
             *  Condition 'current_len+segment_len>=result_size' is always false [knownConditionTrueFalse]
             */
            if (current_len + segment_len >= result_size) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_len, input + last_pos, segment_len);
            current_len += segment_len;
            result[current_len] = '\0';
        }
        
        if (current_len + 2 > result_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        
        result[current_len] = ' ';
        current_len++;
        result[current_len] = '\0';
        
        last_pos = match_end;
        pos = match_end;
    }
    
    size_t remaining_len = input_len - last_pos;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'current_len+remaining_len+1>result_size' is not redundant
     */
    if (current_len + remaining_len + 1 > result_size) {
        regfree(&regex);
        free(result);
        return NULL;
    }
    
    if (remaining_len > 0) {
        /* Possible weaknesses found:
         *  Condition 'current_len+remaining_len>=result_size' is always false [knownConditionTrueFalse]
         *  Condition 'current_len+remaining_len>=result_size' is always false
         */
        if (current_len + remaining_len >= result_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + current_len, input + last_pos, remaining_len);
        current_len += remaining_len;
        result[current_len] = '\0';
    }
    
    regfree(&regex);
    
    temp = realloc(result, current_len + 1);
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