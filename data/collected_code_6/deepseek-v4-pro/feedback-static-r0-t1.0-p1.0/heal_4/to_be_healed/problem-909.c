#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

static bool safe_strlen(const char *str, size_t max_len, size_t *out_len) {
    if (str == NULL || out_len == NULL) {
        return false;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len >= max_len) {
        return false;
    }
    *out_len = len;
    return true;
}

static void reverse_string(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

static bool is_palindrome(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

static bool decrement_string(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    int i = (int)len - 1;
    while (i >= 0 && str[i] == '0') {
        str[i] = '9';
        i--;
    }
    if (i >= 0) {
        str[i]--;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'len>1' is not redundant
     */
    if (str[0] == '0' && len > 1) {
        /* Possible weaknesses found:
         *  Condition 'len>0' is always true [knownConditionTrueFalse]
         *  Condition 'len>0' is always true
         */
        if (len > 0) {
            memmove(str, str + 1, len);
        }
        str[len - 1] = '\0';
    }
    return true;
}

static void make_palindrome_from_left(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }
    for (size_t i = 0; i < len / 2; i++) {
        str[len - 1 - i] = str[i];
    }
}

static bool adjust_for_smaller_palindrome(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    int mid = ((int)len - 1) / 2;
    int i = mid;
    while (i >= 0 && str[i] == '0') {
        str[i] = '9';
        if ((int)len - 1 - i != i) {
            str[(int)len - 1 - i] = '9';
        }
        i--;
    }
    if (i >= 0) {
        str[i]--;
        if ((int)len - 1 - i != i) {
            str[(int)len - 1 - i] = str[i];
        }
    } else {
        /* Possible weaknesses found:
         *  Assuming that condition 'len==1' is not redundant
         */
        if (len == 1) {
            return false;
        }
        /* Possible weaknesses found:
         *  Assignment 'new_len=len-1', assigned value is greater than 0
         */
        size_t new_len = len - 1;
        /* Possible weaknesses found:
         *  Condition 'new_len==0' is always false
         *  Condition 'new_len==0' is always false [knownConditionTrueFalse]
         */
        if (new_len == 0) {
            return false;
        }
        memset(str, '9', new_len);
        str[new_len] = '\0';
    }
    return true;
}

static bool remove_leading_zero(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    if (str[0] == '0' && len > 1) {
        memmove(str, str + 1, len);
        str[len - 1] = '\0';
        return true;
    }
    return false;
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

    size_t len;
    if (!safe_strlen(str, sizeof(str), &len)) {
        return 0;
    }
    
    if (is_palindrome(str, len)) {
        if (!decrement_string(str, len)) {
            return 0;
        }
        if (!safe_strlen(str, sizeof(str), &len)) {
            return 0;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char original[64];
    if (len >= sizeof(original)) {
        return 0;
    }
    if (len + 1 > sizeof(original)) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(original, str, len + 1);

    make_palindrome_from_left(str, len);
    
    if (strcmp(str, original) >= 0) {
        if (!adjust_for_smaller_palindrome(str, len)) {
            return 0;
        }
        if (!safe_strlen(str, sizeof(str), &len)) {
            return 0;
        }
        remove_leading_zero(str, len);
        if (!safe_strlen(str, sizeof(str), &len)) {
            return 0;
        }
    }

    char *endptr;
    errno = 0;
    long long result = strtoll(str, &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return 0;
    }
    return result;
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