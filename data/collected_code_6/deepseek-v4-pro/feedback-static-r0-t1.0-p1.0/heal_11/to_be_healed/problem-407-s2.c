#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define MAX_DIGIT_LEN 64

static int compare_asc(const void *a, const void *b) {
    unsigned char ca = *(unsigned char*)a;
    unsigned char cb = *(unsigned char*)b;
    if (ca > cb) return 1;
    if (ca < cb) return -1;
    return 0;
}

static int compare_desc(const void *a, const void *b) {
    unsigned char ca = *(unsigned char*)a;
    unsigned char cb = *(unsigned char*)b;
    if (cb > ca) return 1;
    if (cb < ca) return -1;
    return 0;
}

long long next_bigger_number(long long n) {
    if (n < 0) return -1;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[MAX_DIGIT_LEN];
    int written = snprintf(digits, sizeof(digits), "%lld", n);
    if (written < 0 || written >= (int)sizeof(digits)) {
        return -1;
    }
    
    int len = written;
    if (len < 2 || len >= MAX_DIGIT_LEN) {
        return -1;
    }
    
    if (digits[len] != '\0') {
        return -1;
    }
    
    int i;
    for (i = len - 2; i >= 0; i--) {
        if (digits[i] < digits[i + 1]) {
            break;
        }
    }
    
    if (i < 0) {
        return -1;
    }
    
    int j;
    for (j = len - 1; j > i; j--) {
        if (digits[j] > digits[i]) {
            break;
        }
    }
    
    if (j <= i) {
        return -1;
    }
    
    char temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;
    
    int right_len = len - i - 1;
    if (right_len > 0 && i + 1 + right_len <= MAX_DIGIT_LEN) {
        qsort(digits + i + 1, right_len, sizeof(char), compare_asc);
    } else if (right_len > 0) {
        return -1;
    }
    
    digits[len] = '\0';
    
    errno = 0;
    char *endptr;
    long long result = strtoll(digits, &endptr, 10);
    if (errno == ERANGE) {
        return -1;
    }
    if (endptr != digits + len) {
        return -1;
    }
    if (*endptr != '\0') {
        return -1;
    }
    
    if (result <= n) {
        return -1;
    }
    
    return result;
}

int main(void) {
    long long test_cases[] = {
        12, 21, 513, 2017, 9, 111, 531, 123456789,
        -5, 0, 10, 999999999999999999
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        long long result = next_bigger_number(test_cases[i]);
        printf("%lld -> %lld\n", test_cases[i], result);
    }
    
    return 0;
}