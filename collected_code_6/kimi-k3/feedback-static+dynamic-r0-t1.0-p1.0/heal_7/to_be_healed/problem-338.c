#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int countSubstrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *str = NULL;
    size_t capacity = 0;
    size_t len = 0;
    int c;
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_str = realloc(str, new_capacity);
            if (new_str == NULL) {
                free(str);
                return 1;
            }
            str = new_str;
            capacity = new_capacity;
        }
        str[len++] = (char)c;
    }
    
    if (str != NULL) {
        str[len] = '\0';
        int result = countSubstrings(str, len);
        printf("%d\n", result);
        free(str);
    }
    
    return 0;
}