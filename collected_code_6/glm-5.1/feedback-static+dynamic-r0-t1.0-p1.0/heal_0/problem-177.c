#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int check_lcm_range(int a, int b, int low, int high) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    if (high <= 0 || low > high) {
        return 0;
    }
    long long g = gcd(a, b);
    long long l = (long long)a * (b / g);
    if (l > 2147483647LL) {
        return 0;
    }
    if (l >= low && l <= high) {
        return 1;
    }
    return 0;
}

void find_numbers(int low, int high, int *r1, int *r2) {
    *r1 = -1;
    *r2 = -1;
    if (low <= 0 || high <= 0 || low > high) {
        return;
    }
    int size = high + 1;
    int *sieve = (int *)malloc(size * sizeof(int));
    if (!sieve) {
        return;
    }
    for (int i = 0; i < size; i++) {
        sieve[i] = 0;
    }
    for (int i = 2; i < size; i++) {
        if (sieve[i] == 0) {
            for (long long j = (long long)i * i; j < size; j += i) {
                sieve[j] = 1;
            }
        }
    }
    for (int i = 2; i < size; i++) {
        if (sieve[i] == 0) {
            for (int j = i + 1; j < size; j++) {
                if (sieve[j] == 0) {
                    long long l = (long long)i * j;
                    if (l > 2147483647LL) {
                        continue;
                    }
                    if (l >= low && l <= high) {
                        *r1 = i;
                        *r2 = j;
                        free(sieve);
                        return;
                    }
                }
            }
        }
    }
    free(sieve);
}

int main() {
    int low = 10;
    int high = 50;
    int a, b;
    find_numbers(low, high, &a, &b);
    if (a != -1 && b != -1) {
        printf("%d %d\n", a, b);
    } else {
        printf("Not found\n");
    }
    return 0;
}