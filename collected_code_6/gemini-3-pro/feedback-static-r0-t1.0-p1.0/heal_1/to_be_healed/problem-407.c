#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

long long next_bigger_number(long long n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[32];
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(str, "%lld", n);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int i, j;

    for (i = len - 2; i >= 0; i--) {
        if (str[i] < str[i + 1]) {
            break;
        }
    }

    if (i < 0) {
        return -1;
    }

    int min_idx = i + 1;
    for (j = i + 1; j < len; j++) {
        if (str[j] > str[i] && str[j] < str[min_idx]) {
            min_idx = j;
        }
    }

    swap(&str[i], &str[min_idx]);

    qsort(str + i + 1, len - i - 1, sizeof(char), compare_chars);

    long long result = strtoll(str, NULL, 10);
    return result;
}

int main() {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return 1;
    }
    
    long long result = next_bigger_number(n);
    printf("%lld\n", result);
    
    return 0;
}