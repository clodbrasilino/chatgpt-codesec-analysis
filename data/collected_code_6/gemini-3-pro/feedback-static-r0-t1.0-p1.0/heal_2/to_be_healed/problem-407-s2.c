#include <stdio.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}

long long next_bigger_number(long long n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[32];
    int len = snprintf(str, sizeof(str), "%lld", n);
    
    if (len < 0 || len >= (int)sizeof(str) || len <= 1) {
        return -1;
    }
    
    int i;
    for (i = len - 2; i >= 0; i--) {
        if (str[i] < str[i + 1]) {
            break;
        }
    }
    
    if (i < 0) return -1;
    
    int min_idx = i + 1;
    for (int j = i + 1; j < len; j++) {
        if (str[j] > str[i] && str[j] < str[min_idx]) {
            min_idx = j;
        }
    }
    
    swap(&str[i], &str[min_idx]);
    qsort(&str[i + 1], len - i - 1, sizeof(char), compare);
    
    char *endptr;
    long long result = strtoll(str, &endptr, 10);
    
    if (*endptr != '\0') {
        return -1;
    }
    
    return result;
}

int main(void) {
    long long num;
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (num < 0) {
        return 1;
    }
    
    long long result = next_bigger_number(num);
    printf("%lld\n", result);
    
    return 0;
}