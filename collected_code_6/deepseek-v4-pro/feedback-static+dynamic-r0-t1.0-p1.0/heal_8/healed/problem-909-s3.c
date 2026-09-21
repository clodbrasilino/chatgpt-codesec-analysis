#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

static bool decrement_string(char *str, size_t len) {
    int i = (int)len - 1;
    while (i >= 0 && str[i] == '0') {
        str[i] = '9';
        i--;
    }
    if (i < 0) {
        return false;
    }
    str[i]--;
    if (str[0] == '0' && len > 1) {
        memmove(str, str + 1, len);
        str[len - 1] = '\0';
    }
    return true;
}

static bool is_numeric_string(const char *str, size_t len) {
    if (len == 0) return false;
    for (size_t i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

char *previous_palindrome(const char *num) {
    if (num == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (num[len] != '\0') {
        len++;
        if (len > 1024) {
            return NULL;
        }
    }
    
    if (len == 0) {
        return NULL;
    }
    
    if (!is_numeric_string(num, len)) {
        return NULL;
    }
    
    size_t alloc_size = len + 1;
    if (alloc_size <= len) {
        return NULL;
    }
    
    char *result = (char *)malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }
    
    if (len >= alloc_size) {
        free(result);
        return NULL;
    }
    memcpy(result, num, len);
    result[len] = '\0';
    
    size_t current_len = len;
    if (!decrement_string(result, current_len)) {
        free(result);
        return NULL;
    }
    
    while (!is_palindrome(result, current_len)) {
        current_len = 0;
        while (result[current_len] != '\0') {
            current_len++;
            if (current_len > 1024) {
                free(result);
                return NULL;
            }
        }
        
        if (current_len == 0) {
            free(result);
            return NULL;
        }
        
        if (!decrement_string(result, current_len)) {
            free(result);
            return NULL;
        }
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "100",
        "123",
        "999",
        "1000",
        "12345",
        "9",
        "10",
        "11",
        "12321",
        "100000",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = previous_palindrome(test_cases[i]);
        if (result != NULL) {
            printf("Previous palindrome of %s is %s\n", test_cases[i], result);
            free(result);
        } else {
            printf("No previous palindrome found for %s\n", test_cases[i]);
        }
    }
    
    return 0;
}