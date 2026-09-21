#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* next_smallest_palindrome(const char* num, size_t len) {
    if (len == 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        if (!result) return NULL;
        result[0] = '1';
        result[1] = '\0';
        return result;
    }

    char* result = (char*)malloc((len + 2) * sizeof(char));
    if (!result) return NULL;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    if (left < 0 || (unsigned char)result[left] < (unsigned char)result[right]) {
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

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num[102] = {0};

    printf("Enter a number: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%101s", num) != 1) {
        printf("Input error\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(num);

    int all_nines = 1;
    for (size_t i = 0; i < len; i++) {
        if (num[i] < '0' || num[i] > '9') {
            printf("Invalid input: not a number\n");
            return 1;
        }
        if (num[i] != '9') {
            all_nines = 0;
        }
    }

    if (all_nines && len == 101) {
        printf("Next smallest palindrome: 1");
        for (size_t i = 0; i < 100; i++) {
            printf("0");
        }
        printf("1\n");
        return 0;
    }

    char* result = next_smallest_palindrome(num, len);
    if (result) {
        printf("Next smallest palindrome: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}