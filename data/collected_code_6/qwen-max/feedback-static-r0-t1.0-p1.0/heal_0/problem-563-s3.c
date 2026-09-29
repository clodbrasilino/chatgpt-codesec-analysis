#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* extract_quoted(const char *input) {
    if (input == NULL) return NULL;
    
    const char *start = strchr(input, '"');
    if (start == NULL) return NULL;
    start++; // Skip the opening quote
    
    const char *end = strchr(start, '"');
    if (end == NULL) return NULL;
    
    size_t len = end - start;
    char *result = malloc(len + 1);
    if (result == NULL) return NULL;
    
    strncpy(result, start, len);
    result[len] = '\0';
    
    return result;
}

int main() {
    const char *input = "This is a \"sample\" string with \"quoted\" values.";
    char *result = extract_quoted(input);
    
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("No quoted value found.\n");
    }
    
    return 0;
}