#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str, size_t len) {
    size_t i;
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

void increment_string(char *str, size_t len) {
    int carry = 1;
    int i;
    for (i = (int)len - 1; i >= 0 && carry; i--) {
        int digit = (str[i] - '0') + carry;
        str[i] = (char)('0' + (digit % 10));
        carry = digit / 10;
    }
}

char* next_smallest_palindrome(unsigned long long num) {
    char buffer[32];
    char *result;
    size_t len;
    size_t i;
    
    if (num == 0) {
        result = malloc(2);
        if (result != NULL) {
            result[0] = '1';
            result[1] = '\0';
        }
        return result;
    }
    
    snprintf(buffer, sizeof(buffer), "%llu", num);
    len = strlen(buffer);
    
    result = malloc(len + 2);
    if (result == NULL) {
        return NULL;
    }
    
    strcpy(result, buffer);
    
    for (i = 0; i < len / 2; i++) {
        result[len - 1 - i] = result[i];
    }
    
    if (strcmp(result, buffer) > 0) {
        return result;
    }
    
    size_t mid = (len - 1) / 2;
    int carry = 1;
    int idx = (int)mid;
    
    while (idx >= 0 && carry) {
        int digit = (result[idx] - '0') + carry;
        result[idx] = (char)('0' + (digit % 10));
        carry = digit / 10;
        idx--;
    }
    
    if (carry) {
        memmove(result + 1, result, len + 1);
        result[0] = '1';
        len++;
        result[len] = '\0';
        for (i = 1; i < len; i++) {
            result[i] = '0';
        }
        result[len - 1] = '1';
        return result;
    }
    
    for (i = 0; i < len / 2; i++) {
        result[len - 1 - i] = result[i];
    }
    
    return result;
}

int main(void) {
    unsigned long long num;
    char *palindrome;
    
    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    palindrome = next_smallest_palindrome(num);
    if (palindrome == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Next smallest palindrome: %s\n", palindrome);
    
    free(palindrome);
    return 0;
}