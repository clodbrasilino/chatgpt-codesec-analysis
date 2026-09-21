#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(const char *str, size_t len) {
    size_t i;
    if (str == NULL) {
        return false;
    }
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

void increment_string(char *str, size_t len) {
    int carry = 1;
    size_t i;
    if (str == NULL || len == 0) {
        return;
    }
    for (i = len; i > 0 && carry; i--) {
        int digit = (str[i - 1] - '0') + carry;
        str[i - 1] = (char)('0' + (digit % 10));
        carry = digit / 10;
    }
}

char* next_smallest_palindrome(unsigned long long num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *result;
    size_t len;
    size_t i;
    size_t mid;
    int carry;
    int idx;
    int written;
    size_t result_size;
    
    if (num == 0) {
        result = malloc(2);
        if (result != NULL) {
            result[0] = '1';
            result[1] = '\0';
        }
        return result;
    }
    
    written = snprintf(buffer, sizeof(buffer), "%llu", num);
    if (written < 0 || (size_t)written >= sizeof(buffer)) {
        return NULL;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || len >= sizeof(buffer)) {
        return NULL;
    }
    
    result_size = len + 3;
    result = calloc(result_size, sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    written = snprintf(result, result_size, "%s", buffer);
    if (written < 0 || (size_t)written >= result_size) {
        free(result);
        return NULL;
    }
    
    for (i = 0; i < len / 2; i++) {
        result[len - 1 - i] = result[i];
    }
    
    if (strcmp(result, buffer) > 0) {
        return result;
    }
    
    mid = (len - 1) / 2;
    carry = 1;
    idx = (int)mid;
    
    while (idx >= 0 && carry) {
        int digit = (result[idx] - '0') + carry;
        result[idx] = (char)('0' + (digit % 10));
        carry = digit / 10;
        idx--;
    }
    
    if (carry) {
        if (len + 2 < result_size) {
            memmove(result + 1, result, len + 1);
            result[0] = '1';
            len++;
            result[len] = '\0';
            for (i = 1; i < len - 1; i++) {
                result[i] = '0';
            }
            result[len - 1] = '1';
        } else {
            free(result);
            return NULL;
        }
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