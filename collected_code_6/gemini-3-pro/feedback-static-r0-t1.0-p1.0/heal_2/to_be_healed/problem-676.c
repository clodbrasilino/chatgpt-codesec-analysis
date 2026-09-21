#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

char* remove_non_alnum_regex(const char *input);

char* remove_non_alnum_regex(const char *input) {
    if (!input) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    
    char *result = (char *)malloc(len + 1);
    if (!result) {
        regfree(&regex);
        return NULL;
    }
    
    result[0] = '\0';
    size_t out_pos = 0;
    const char *cursor = input;
    regmatch_t pmatch[1];

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_len = (size_t)(pmatch[0].rm_eo - pmatch[0].rm_so);
        
        if (out_pos + match_len > len) {
            break; 
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + out_pos, cursor + pmatch[0].rm_so, match_len);
        out_pos += match_len;
        result[out_pos] = '\0';
        
        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
    
    return result;
}

int main(void) {
    const char *test_str = "C@ding 1s fun! _R3gex#2023";
    char *cleaned = remove_non_alnum_regex(test_str);
    
    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
        cleaned = NULL;
    } else {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}