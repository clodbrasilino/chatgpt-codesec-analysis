#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_quotes(const char* input, int* count) {
    if (!input || !count) {
        if (count) *count = 0;
        return NULL;
    }

    int capacity = 10;
    int found_count = 0;
    char** results = malloc(capacity * sizeof(char*));
    if (!results) {
        *count = 0;
        return NULL;
    }

    const char* p = input;
    const char* start = NULL;

    while (*p != '\0') {
        if (*p == '"') {
            if (start == NULL) {
                start = p + 1;
            } else {
                size_t len = p - start;
                char* extracted = malloc(len + 1);
                if (!extracted) {
                    for (int i = 0; i < found_count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    *count = 0;
                    return NULL;
                }
                
                strncpy(extracted, start, len);
                extracted[len] = '\0';

                if (found_count >= capacity) {
                    capacity *= 2;
                    char** temp = realloc(results, capacity * sizeof(char*));
                    if (!temp) {
                        free(extracted);
                        for (int i = 0; i < found_count; i++) {
                            free(results[i]);
                        }
                        free(results);
                        *count = 0;
                        return NULL;
                    }
                    results = temp;
                }
                
                results[found_count++] = extracted;
                start = NULL;
            }
        }
        p++;
    }

    *count = found_count;
    if (found_count == 0) {
        free(results);
        return NULL;
    }

    return results;
}

int main(void) {
    const char* text = "Hello \"world\", this is a \"test\" string with \"multiple\" quotes.";
    int count = 0;
    
    char** extracted = extract_quotes(text, &count);
    
    if (extracted) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }
    
    return 0;
}