#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_smart_number(int n) {
    if (n <= 0) {
        return -1;
    }

    long long max_limit_ll = (long long)n * 20;
    if (max_limit_ll > INT_MAX) {
        return -1;
    }
    int max_limit = (int)max_limit_ll;

    int *count = (int *)calloc(max_limit + 1, sizeof(int));
    if (count == NULL) {
        return -1;
    }

    for (int i = 2; i <= max_limit; i++) {
        if (count[i] == 0) {
            for (long long j = (long long)i * i; j <= max_limit; j += i) {
                count[j]++;
            }
        }
    }

    int result = 0;
    int found = 0;
    for (int i = 2; i <= max_limit; i++) {
        if (count[i] >= 2) {
            found++;
            if (found == n) {
                result = i;
                break;
            }
        }
    }

    free(count);

    if (result == 0) {
        return -1;
    }

    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
        return 1;
    }

    int res = find_nth_smart_number(n);
    if (res == -1) {
        return 1;
    }

    printf("%d\n", res);

    return 0;
}