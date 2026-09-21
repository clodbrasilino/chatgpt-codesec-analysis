#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

#define MAX_STR_LEN 64

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

static bool decrement_string(char *str, size_t len, size_t max_len) {
    if (str == NULL || len == 0 || len >= max_len) {
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
    if (str[0] == '0' && len > 1) {
        if (len > max_len - 1) {
            return false;
        }
        memmove(str, str + 1, len - 1);
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

static bool adjust_for_smaller_palindrome(char *str, size_t len, size_t max_len) {
    if (str == NULL || len == 0 || len >= max_len) {
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
        if (len <= 1) {
            return false;
        }
        if (max_len == 0 || len - 1 >= max_len) {
            return false;
        }
        memset(str, '9', len - 1);
        str[len - 1] = '\0';
    }
    return true;
}

static bool remove_leading_zero(char *str, size_t len, size_t max_len) {
    if (str == NULL || len == 0 || len >= max_len) {
        return false;
    }
    if (str[0] == '0' && len > 1) {
        memmove(str, str + 1, len - 1);
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

    char str[MAX_STR_LEN];
    int written = snprintf(str, sizeof(str), "%lld", num);
    if (written < 0 || (size_t)written >= sizeof(str)) {
        return 0;
    }

    size_t max_len = sizeof(str);
    size_t len;
    if (!safe_strlen(str, max_len, &len)) {
        return 0;
    }
    
    if (is_palindrome(str, len)) {
        if (!decrement_string(str, len, max_len)) {
            return 0;
        }
        if (!safe_strlen(str, max_len, &len)) {
            return 0;
        }
    }

    char original[MAX_STR_LEN];
    if (len >= sizeof(original)) {
        return 0;
    }
    if (len + 1 > sizeof(original)) {
        return 0;
    }
    memcpy(original, str, len + 1);

    make_palindrome_from_left(str, len);
    
    if (strcmp(str, original) >= 0) {
        if (!adjust_for_smaller_palindrome(str, len, max_len)) {
            return 0;
        }
        if (!safe_strlen(str, max_len, &len)) {
            return 0;
        }
        remove_leading_zero(str, len, max_len);
        if (!safe_strlen(str, max_len, &len)) {
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