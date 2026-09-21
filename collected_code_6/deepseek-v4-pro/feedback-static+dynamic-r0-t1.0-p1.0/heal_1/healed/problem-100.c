#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* next_smallest_palindrome(const char* num, size_t len) {
    char* result = (char*)malloc((len + 2) * sizeof(char));
    if (!result) return NULL;
    
    memcpy(result, num, len);
    result[len] = '\0';
    
    int n = (int)len;
    int left = n / 2 - 1;
    int right = (n + 1) / 2;
    
    while (left >= 0 && result[left] == result[right]) {
        left--;
        right++;
    }
    
    int need_increment = 0;
    if (left < 0 || result[left] < result[right]) {
        need_increment = 1;
    }
    
    if (need_increment) {
        int carry = 1;
        left = (n - 1) / 2;
        while (left >= 0 && carry) {
            if (result[left] == '9') {
                result[left] = '0';
                carry = 1;
            } else {
                result[left]++;
                carry = 0;
            }
            left--;
        }
        
        if (carry) {
            char* new_result = (char*)malloc((n + 2) * sizeof(char));
            if (!new_result) {
                free(result);
                return NULL;
            }
            new_result[0] = '1';
            for (int i = 0; i < n; i++) {
                new_result[i + 1] = '0';
            }
            new_result[n + 1] = '\0';
            free(result);
            result = new_result;
            n = n + 1;
        }
    }
    
    for (int i = 0; i < n / 2; i++) {
        result[n - 1 - i] = result[i];
    }
    
    result[n] = '\0';
    return result;
}

int main() {
    char num[101];
    
    printf("Enter a number: ");
    if (scanf("%100s", num) != 1) {
        printf("Input error\n");
        return 1;
    }
    
    size_t len = strlen(num);
    char* result = next_smallest_palindrome(num, len);
    if (result) {
        printf("Next smallest palindrome: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    
    return 0;
}