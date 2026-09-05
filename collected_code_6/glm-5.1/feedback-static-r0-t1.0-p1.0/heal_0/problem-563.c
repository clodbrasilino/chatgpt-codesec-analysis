#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_quoted(const char *str, size_t *count) {
    size_t len = strlen(str);
    size_t capacity = 10;
    char **results = malloc(capacity * sizeof(char *));
    if (!results) {
        return NULL;
    }
    
    *count = 0;
    
    for (size_t i = 0; i < len; ) {
        if (str[i] == '"') {
            size_t start = i + 1;
            size_t end = start;
            
            while (end < len && str[end] != '"') {
                end++;
            }
            
            if (end < len) {
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
                
                memcpy(substr, str + start, substr_len);
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
    char **values = extract_quoted(text, &count);
    
    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }
    
    return 0;
}