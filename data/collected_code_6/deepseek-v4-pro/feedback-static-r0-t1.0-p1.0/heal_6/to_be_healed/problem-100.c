#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* next_smallest_palindrome(const char* num) {
    if (!num) return NULL;
    
    size_t n = strnlen(num, 1024);
    if (n == 0 || n >= 1024) return NULL;
    
    for (size_t i = 0; i < n; i++) {
        if (num[i] < '0' || num[i] > '9') return NULL;
    }
    
    size_t max_len = n + 3;
    char* result = (char*)calloc(max_len, sizeof(char));
    if (!result) return NULL;
    
    /* Possible weaknesses found:
     *  Assuming condition 'n+1>max_len' is false
     */
    if (n + 1 > max_len) {
        free(result);
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  Condition 'n+1<=max_len' is always true [knownConditionTrueFalse]
     *  Condition 'n+1<=max_len' is always true
     */
    if (n + 1 <= max_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, num, n);
        result[n] = '\0';
    } else {
        free(result);
        return NULL;
    }
    
    int left = (int)(n / 2) - 1;
    int right = (int)((n + 1) / 2);
    
    while (left >= 0 && result[left] == result[right]) {
        left--;
        right++;
    }
    
    int need_increment = 0;
    if (left < 0 || (unsigned char)result[left] < (unsigned char)result[right]) {
        need_increment = 1;
    }
    
    if (need_increment) {
        int carry = 1;
        left = (int)((n - 1) / 2);
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
            size_t new_len = n + 2;
            if (new_len > max_len) {
                char* new_result = (char*)realloc(result, new_len);
                if (!new_result) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                max_len = new_len;
            }
            
            if (max_len < 2 || new_len > max_len) {
                free(result);
                return NULL;
            }
            memmove(result + 1, result, n);
            result[0] = '1';
            if (n < max_len) {
                result[n] = '0';
            }
            if (n + 1 < max_len) {
                result[n + 1] = '\0';
            }
            n = n + 1;
        }
    }
    
    for (size_t i = 0; i < n / 2; i++) {
        if (n - 1 - i < max_len && i < max_len) {
            result[n - 1 - i] = result[i];
        }
    }
    
    if (n < max_len) {
        result[n] = '\0';
    } else {
        free(result);
        return NULL;
    }
    
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num[101] = {0};
    
    printf("Enter a number: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    size_t len = strnlen(num, sizeof(num));
    if (len >= sizeof(num) - 1 && num[sizeof(num) - 1] != '\0') {
        printf("Invalid input: input too long\n");
        return 1;
    }
    
    for (size_t i = 0; i < sizeof(num) && num[i] != '\0'; i++) {
        if (num[i] < '0' || num[i] > '9') {
            printf("Invalid input: must contain only digits\n");
            return 1;
        }
    }
    
    char* result = next_smallest_palindrome(num);
    if (result) {
        printf("Next smallest palindrome: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed or invalid input\n");
    }
    
    return 0;
}