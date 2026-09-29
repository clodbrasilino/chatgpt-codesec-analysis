#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
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
        size_t remaining = len - 1;
        if (remaining < len) {
            memmove(str, str + 1, remaining + 1);
        }
    }
}

static void make_palindrome_from_left(char *str) {
    if (str == NULL) {
        return;
    }
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

    char str[64];
    int written = snprintf(str, sizeof(str), "%lld", num);
    if (written < 0 || (size_t)written >= sizeof(str)) {
        return 0;
    }
    
    if (is_palindrome(str)) {
        decrement_string(str);
    }

    size_t len = strlen(str);
    if (len >= 64) {
        return 0;
    }
    
    char original[64];
    memcpy(original, str, len + 1);

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
                if (len < 64) {
                    memset(str, '9', len);
                    str[len] = '\0';
                }
            }
        }
        
        if (len > 1 && str[0] == '0') {
            if (len <= 63) {
                memmove(str, str + 1, len);
                str[len - 1] = '\0';
            }
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