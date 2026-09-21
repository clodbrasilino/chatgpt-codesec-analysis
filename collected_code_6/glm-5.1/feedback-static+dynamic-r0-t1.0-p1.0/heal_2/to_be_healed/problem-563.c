#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_quoted(const char *str, size_t str_len, size_t *count) {
    size_t capacity = 10;
    char **results = malloc(capacity * sizeof(char *));
    if (!results) {
        return NULL;
    }
    
    *count = 0;
    
    for (size_t i = 0; i < str_len; ) {
        if (str[i] == '"') {
            size_t start = i + 1;
            size_t end = start;
            
            while (end < str_len && str[end] != '"') {
                end++;
            }
            
            if (end < str_len) {
                if (*count >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(results, capacity * sizeof(char *));
                    if (!temp) {
                        for (size_t j = 0; j < *count; j++) {
                            free(results[j]);
                        }
                        free(results);
                        return NULL;
                    }
                    results = temp;
                }
                
                size_t substr_len = end - start;
                char *substr = malloc(substr_len + 1);
                if (!substr) {
                    for (size_t j = 0; j < *count; j++) {
                        free(results[j]);
                    }
                    free(results);
                    return NULL;
                }
                
                if (substr_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(substr, str + start, substr_len);
                }
                substr[substr_len] = '\0';
                results[*count] = substr;
                (*count)++;
                i = end + 1;
            } else {
                i = end;
            }
        } else {
            i++;
        }
    }
    
    return results;
}

int main(void) {
    const char *text = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    size_t count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_len = strlen(text);
    char **values = extract_quoted(text, text_len, &count);
    
    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }
    
    return 0;
}