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
    size_t i = len;
    while (i > 0 && str[i - 1] == '0') {
        str[i - 1] = '9';
        i--;
    }
    if (i > 0) {
        str[i - 1]--;
    }
    if (str[0] == '0') {
        if (len > 1) {
            memmove(str, str + 1, len);
            str[len - 1] = '\0';
        } else {
            str[0] = '\0';
            return true;
        }
    }
    return false;
}

char *previous_palindrome(const char *num) {
    if (num == NULL || *num == '\0') {
        return NULL;
    }
    
    size_t len = 0;
    while (num[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        return NULL;
    }
    
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    if (len >= len + 1) {
        free(result);
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        result[i] = num[i];
    }
    result[len] = '\0';
    
    decrement_string(result, len);
    
    size_t new_len = 0;
    while (result[new_len] != '\0') {
        new_len++;
    }
    
    if (new_len == 0) {
        free(result);
        return NULL;
    }
    
    while (!is_palindrome(result, new_len)) {
        if (decrement_string(result, new_len)) {
            free(result);
            return NULL;
        }
        new_len = 0;
        while (result[new_len] != '\0') {
            new_len++;
        }
        if (new_len == 0) {
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