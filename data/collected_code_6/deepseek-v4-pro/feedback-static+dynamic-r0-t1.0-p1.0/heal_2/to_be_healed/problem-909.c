#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

static bool is_palindrome(const char *str) {
    if (str == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

static void decrement_string(char *str) {
    if (str == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }
    size_t i = len;
    while (i > 0 && str[i - 1] == '0') {
        str[i - 1] = '9';
        i--;
    }
    if (i > 0) {
        str[i - 1]--;
    }
    if (str[0] == '0' && len > 1) {
        memmove(str, str + 1, len);
        str[len - 1] = '\0';
    }
}

static void make_palindrome_from_left(char *str) {
    if (str == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        str[len - 1 - i] = str[i];
    }
}

long long previous_palindrome(long long num) {
    if (num <= 0) {
        return 0;
    }
    if (num <= 10) {
        return num - 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[64];
    int written = snprintf(str, sizeof(str), "%lld", num);
    if (written < 0 || (size_t)written >= sizeof(str)) {
        return 0;
    }
    
    if (is_palindrome(str)) {
        decrement_string(str);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char original[64];
    size_t copy_len = len < sizeof(original) - 1 ? len : sizeof(original) - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(original, str, copy_len);
    original[copy_len] = '\0';

    make_palindrome_from_left(str);
    
    if (strcmp(str, original) >= 0) {
        size_t mid = (len > 0) ? (len - 1) / 2 : 0;
        size_t i = mid;
        while (i < len && str[i] == '0') {
            str[i] = '9';
            if (len - 1 - i != i) {
                str[len - 1 - i] = '9';
            }
            if (i == 0) {
                break;
            }
            i--;
        }
        if (i < len && str[i] > '0') {
            str[i]--;
            if (len - 1 - i != i) {
                str[len - 1 - i] = str[i];
            }
        } else {
            if (len > 0) {
                len--;
                memset(str, '9', len);
                str[len] = '\0';
            }
        }
        
        if (len > 1 && str[0] == '0') {
            memmove(str, str + 1, len);
            str[len - 1] = '\0';
        }
    }

    return atoll(str);
}

int main(void) {
    long long test_cases[] = {100, 99, 12345, 123456, 99999, 100000, 1, 11, 10001, 12321};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        long long result = previous_palindrome(test_cases[i]);
        printf("Previous palindrome of %lld is %lld\n", test_cases[i], result);
    }

    return 0;
}