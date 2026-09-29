#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **extract_quoted_strings(const char *input, size_t *count) {
    regex_t regex;
    regmatch_t matches[2];
    char **results = NULL;
    size_t capacity = 0;
    int ret;
    
    *count = 0;
    
    if (input == NULL) {
        return NULL;
    }
    
    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }
    
    const char *cursor = input;
    
    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
        if (*count == capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            char **new_results = realloc(results, new_capacity * sizeof(char *));
            if (new_results == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                return NULL;
            }
            results = new_results;
            capacity = new_capacity;
        }
        
        regoff_t start = matches[1].rm_so;
        regoff_t end = matches[1].rm_eo;
        size_t len = (size_t)(end - start);
        
        results[*count] = malloc(len + 1);
        if (results[*count] == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            return NULL;
        }
        
        memcpy(results[*count], cursor + start, len);
        results[*count][len] = '\0';
        
        (*count)++;
        cursor += matches[0].rm_eo;
    }
    
    regfree(&regex);
    
    if (*count == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

void free_extracted_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char *test_string = "This is a \"test\" with \"multiple\" quoted \"values\" here";
    size_t count = 0;
    
    char **extracted = extract_quoted_strings(test_string, &count);
    
    if (extracted == NULL) {
        printf("No quoted strings found or error occurred\n");
        return 1;
    }
    
    printf("Found %zu quoted strings:\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("[%zu]: %s\n", i, extracted[i]);
    }
    
    free_extracted_strings(extracted, count);
    
    return 0;
}