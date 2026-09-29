#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  'ptrdiff_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
  */

static char** allocate_result_array(char** result, int* capacity, int count) {
    if (count >= *capacity) {
        *capacity = *capacity == 0 ? 4 : *capacity * 2;
        char** new_result = realloc(result, *capacity * sizeof(char*));
        return new_result;
    }
    return result;
}

static void cleanup_on_error(char** result, int count, regex_t* regex) {
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
    regfree(regex);
}

char** split_string(const char* input, const char* pattern, int* count) {
    if (input == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         *  'off_t' declared here
         */
        return NULL;
    }

    char** result = NULL;
    int capacity = 0;
    *count = 0;

    const char* current = input;
    const char* search_start = input;
    regmatch_t match;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    while (1) {
        int match_result = regexec(&regex, search_start, 1, &match, 0);
        
        if (match_result == REG_NOMATCH) {
            /* Possible weaknesses found:
             *  unknown type name 'ptrdiff_t'
             *  use of undeclared identifier 'ptrdiff_t'
             */
            ptrdiff_t offset = current - input;
            /* Possible weaknesses found:
             *  expected ')' before 'input_len'
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'ptrdiff_t'
             *  use of undeclared identifier 'offset'
             *  'ptrdiff_t' undeclared (first use in this function)
             *  'ptrdiff_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
             */
            if (offset < (ptrdiff_t)input_len) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'offset'; did you mean 'off_t'?
                 */
                size_t remaining_len = input_len - (size_t)offset;
                
                char** new_result = allocate_result_array(result, &capacity, *count);
                if (new_result == NULL) {
                    cleanup_on_error(result, *count, &regex);
                    return NULL;
                }
                result = new_result;
                
                result[*count] = malloc(remaining_len + 1);
                if (result[*count] == NULL) {
                    cleanup_on_error(result, *count, &regex);
                    return NULL;
                }
                
                if (remaining_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[*count], current, remaining_len);
                }
                result[*count][remaining_len] = '\0';
                (*count)++;
            }
            break;
        } else if (match_result != 0) {
            cleanup_on_error(result, *count, &regex);
            return NULL;
        }

        size_t token_len = (size_t)(search_start - current) + (size_t)match.rm_so;
        if (token_len > 0) {
            char** new_result = allocate_result_array(result, &capacity, *count);
            if (new_result == NULL) {
                cleanup_on_error(result, *count, &regex);
                return NULL;
            }
            result = new_result;
            
            char* token = malloc(token_len + 1);
            if (token == NULL) {
                cleanup_on_error(result, *count, &regex);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(token, current, token_len);
            token[token_len] = '\0';
            result[*count] = token;
            (*count)++;
        }

        current = search_start + match.rm_eo;
        search_start = current;

        if (*current == '\0') {
            break;
        }
    }

    regfree(&regex);
    return result;
}

void free_split_result(char** result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* input = "Hello,world;this:is|a test";
    const char* pattern = "[,;:| ]+";
    int count = 0;
    
    char** tokens = split_string(input, pattern, &count);
    
    if (tokens == NULL) {
        printf("Failed to split string\n");
        return 1;
    }
    
    printf("Split into %d tokens:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Token %d: '%s'\n", i, tokens[i]);
    }
    
    free_split_result(tokens, count);
    return 0;
}