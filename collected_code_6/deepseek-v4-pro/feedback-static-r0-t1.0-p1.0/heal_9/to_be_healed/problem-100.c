#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#define MAX_INPUT_LEN 1023
#define MAX_BUFFER_LEN 1024

char* next_smallest_palindrome(const char* num) {
    if (!num) return NULL;
    
    size_t n = strnlen(num, MAX_BUFFER_LEN);
    if (n == 0 || n >= MAX_BUFFER_LEN) return NULL;
    
    for (size_t i = 0; i < n; i++) {
        if (num[i] < '0' || num[i] > '9') return NULL;
    }
    
    /* Possible weaknesses found:
     *  max_len is assigned 'n+3' here.
     */
    size_t max_len = n + 3;
    /* Possible weaknesses found:
     *  Condition 'max_len<n' is always false [knownConditionTrueFalse]
     *  Condition 'max_len<n' is always false
     */
    if (max_len < n) return NULL;
    
    char* result = (char*)calloc(max_len, sizeof(char));
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!result) return NULL;
    
    /* Possible weaknesses found:
     *  Condition 'n>=max_len' is always false
     *  Condition 'n>=max_len' is always false [knownConditionTrueFalse]
     */
    if (n >= max_len) {
        free(result);
        return NULL;
    }
    
    if (n + 1 > max_len) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, num, n);
    result[n] = '\0';
    
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
            /* Possible weaknesses found:
             *  new_len is assigned 'n+2' here.
             */
            size_t new_len = n + 2;
            /* Possible weaknesses found:
             *  Condition 'new_len<n' is always false [knownConditionTrueFalse]
             *  Condition 'new_len<n' is always false
             */
            if (new_len < n || new_len > SIZE_MAX - 1) {
                free(result);
                return NULL;
            }
            
            if (new_len > max_len) {
                max_len = new_len;
            }
            
            char* new_result = (char*)realloc(result, new_len);
            if (!new_result) {
                free(result);
                return NULL;
            }
            result = new_result;
            
            if (n + 2 <= new_len) {
                memmove(result + 1, result, n + 1);
                result[0] = '1';
                result[n] = '0';
                result[n + 1] = '\0';
                n = n + 1;
            } else {
                free(result);
                return NULL;
            }
        }
    }
    
    for (size_t i = 0; i < n / 2; i++) {
        result[n - 1 - i] = result[i];
    }
    
    if (n < max_len) {
        result[n] = '\0';
    }
    
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num[MAX_BUFFER_LEN] = {0};
    
    printf("Enter a number: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%1023s", num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    num[MAX_INPUT_LEN] = '\0';
    
    size_t len = strnlen(num, MAX_BUFFER_LEN);
    if (len >= MAX_BUFFER_LEN) {
        printf("Invalid input: input too long\n");
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
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