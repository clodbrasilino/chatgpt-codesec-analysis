#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_STRING_LENGTH 65535

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str != NULL) {
        while (len < max_len && str[len] != '\0') {
            len++;
        }
    }
    return len;
}

void remove_first_last(char *str, char ch) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    size_t len = safe_strlen(str, MAX_STRING_LENGTH);
    if (len == 0 || len >= MAX_STRING_LENGTH) {
        return;
    }
    
    int first = -1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            first = (int)i;
            break;
        }
    }
    
    if (first == -1) {
        return;
    }
    
    int last = -1;
    for (size_t i = len; i > 0; i--) {
        if (str[i - 1] == ch) {
            last = (int)(i - 1);
            break;
        }
    }
    
    size_t write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < len; read++) {
        if ((int)read == first || (int)read == last) {
            continue;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (write > len || read > len) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        str[write] = str[read];
        write++;
    }
    if (write <= len) {
        str[write] = '\0';
    } else {
        str[len] = '\0';
    }
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last(str1, 'o');
    printf("%s\n", str1);
    
    char str2[] = "a";
    remove_first_last(str2, 'a');
    printf("%s\n", str2);
    
    char str3[] = "aaa";
    remove_first_last(str3, 'a');
    printf("%s\n", str3);
    
    char str4[] = "programming";
    remove_first_last(str4, 'g');
    printf("%s\n", str4);
    
    char str5[] = "test";
    remove_first_last(str5, 'x');
    printf("%s\n", str5);
    
    return 0;
}