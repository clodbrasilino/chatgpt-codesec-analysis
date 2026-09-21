#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void remove_first_last_occurrence(char *str, size_t buffer_size, char ch) {
    if (str == NULL || buffer_size == 0) {
        return;
    }
    
    size_t len = strnlen(str, buffer_size);
    if (len == 0 || len >= buffer_size) {
        return;
    }
    
    size_t first = 0;
    size_t last = 0;
    int found_first = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            first = i;
            found_first = 1;
            break;
        }
    }
    
    if (!found_first) {
        return;
    }
    
    for (size_t i = len; i > 0; i--) {
        if (str[i - 1] == ch) {
            last = i - 1;
            break;
        }
    }
    
    if (first == last) {
        memmove(&str[first], &str[first + 1], len - first);
        return;
    }
    
    memmove(&str[first], &str[first + 1], last - first);
    memmove(&str[last - 1], &str[last], len - last + 1);
}

int main(void) {
    char *str1 = malloc(BUFFER_SIZE);
    char *str2 = malloc(BUFFER_SIZE);
    char *str3 = malloc(BUFFER_SIZE);
    char *str4 = malloc(BUFFER_SIZE);
    
    if (str1 == NULL || str2 == NULL || str3 == NULL || str4 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        return 1;
    }
    
    strncpy(str1, "hello world", BUFFER_SIZE - 1);
    str1[BUFFER_SIZE - 1] = '\0';
    
    strncpy(str2, "programming", BUFFER_SIZE - 1);
    str2[BUFFER_SIZE - 1] = '\0';
    
    strncpy(str3, "a", BUFFER_SIZE - 1);
    str3[BUFFER_SIZE - 1] = '\0';
    
    strncpy(str4, "no match here", BUFFER_SIZE - 1);
    str4[BUFFER_SIZE - 1] = '\0';
    
    printf("Original: %s\n", str1);
    remove_first_last_occurrence(str1, BUFFER_SIZE, 'l');
    printf("Modified: %s\n", str1);
    
    printf("Original: %s\n", str2);
    remove_first_last_occurrence(str2, BUFFER_SIZE, 'r');
    printf("Modified: %s\n", str2);
    
    printf("Original: %s\n", str3);
    remove_first_last_occurrence(str3, BUFFER_SIZE, 'a');
    printf("Modified: %s\n", str3);
    
    printf("Original: %s\n", str4);
    remove_first_last_occurrence(str4, BUFFER_SIZE, 'x');
    printf("Modified: %s\n", str4);
    
    free(str1);
    free(str2);
    free(str3);
    free(str4);
    
    return 0;
}