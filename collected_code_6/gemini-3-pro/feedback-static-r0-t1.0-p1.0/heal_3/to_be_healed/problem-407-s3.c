#include <stdio.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

long long get_next_bigger_number(long long n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[32];
    int len = snprintf(str, sizeof(str), "%lld", n);
    
    if (len < 0 || (size_t)len >= sizeof(str)) {
        return -1;
    }
    
    int i, j;

    for (i = len - 1; i > 0; i--) {
        if (str[i] > str[i - 1]) {
            break;
        }
    }

    if (i == 0) {
        return -1;
    }

    int x = str[i - 1];
    int smallest = i;
    
    for (j = i + 1; j < len; j++) {
        if (str[j] > x && str[j] < str[smallest]) {
            smallest = j;
        }
    }

    swap(&str[smallest], &str[i - 1]);
    qsort(str + i, len - i, sizeof(char), compare);

    char *endptr;
    long long res = strtoll(str, &endptr, 10);
    
    if (*endptr != '\0') {
        return -1;
    }
    
    return res;
}

int main(void) {
    long long n = 218765;
    long long res = get_next_bigger_number(n);
    if (res != -1) {
        printf("%lld\n", res);
    } else {
        printf("-1\n");
    }
    return 0;
}