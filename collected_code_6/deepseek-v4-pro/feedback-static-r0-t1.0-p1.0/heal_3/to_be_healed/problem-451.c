#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_whitespaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]", 0);
    if (reti != 0) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
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
            if (result_index + match.rm_so >= result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, match.rm_so);
            result_index += match.rm_so;
        }
        cursor += match.rm_eo;
        if (match.rm_eo == 0) {
            if (result_index + 1 >= result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result[result_index++] = *cursor;
            if (*cursor != '\0') {
                cursor++;
            }
        }
    }
    
    if (*cursor != '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);
        if (result_index + remaining >= result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_index, cursor, remaining);
        result_index += remaining;
    }
    
    if (result_index >= result_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    result[result_index] = '\0';
    regfree(&regex);
    
    return result;
}

int main(void) {
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