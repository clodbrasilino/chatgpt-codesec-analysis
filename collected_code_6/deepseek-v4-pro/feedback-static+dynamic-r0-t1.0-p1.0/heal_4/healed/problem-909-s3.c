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

static void decrement_string(char *str, size_t len) {
    int i = (int)len - 1;
    while (i >= 0 && str[i] == '0') {
        str[i] = '9';
        i--;
    }
    if (i >= 0) {
        str[i]--;
    }
    if (str[0] == '0' && len > 1) {
        memmove(str, str + 1, len);
        str[len - 1] = '\0';
    }
}

char *previous_palindrome(const char *num) {
    if (num == NULL || *num == '\0') {
        return NULL;
    }
    
    size_t len = strlen(num);
    if (len > 1024) {
        return NULL;
    }
    
    size_t alloc_size = len + 1;
    if (alloc_size < len + 1) {
        return NULL;
    }
    
    char *result = (char *)malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }
    
    if (alloc_size > 0) {
        memcpy(result, num, len + 1);
    } else {
        free(result);
        return NULL;
    }
    
    size_t current_len = len;
    decrement_string(result, current_len);
    
    while (!is_palindrome(result, current_len)) {
        current_len = strlen(result);
        if (current_len == 0 || current_len > 1024) {
            free(result);
            return NULL;
        }
        decrement_string(result, current_len);
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