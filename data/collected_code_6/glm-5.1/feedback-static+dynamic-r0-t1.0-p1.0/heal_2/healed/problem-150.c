#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isInSequence(long long a, long long d, long long num) {
    if (d == 0) {
        return a == num;
    }
    if ((d > 0 && num < a) || (d < 0 && num > a)) {
        return false;
    }
    long long diff;
    if ((num >= 0 && a < 0 && num > LLONG_MAX + a) || (num < 0 && a > 0 && num < LLONG_MIN + a)) {
        return false;
    }
    diff = num - a;
    if (diff == 0) {
        return true;
    }
    if ((diff > 0 && d < 0) || (diff < 0 && d > 0)) {
        return false;
    }
    if (diff == LLONG_MIN && d == -1) {
        return true;
    }
    return diff % d == 0;
}

int main() {
    long long a, d, num;
    if (scanf("%lld %lld %lld", &a, &d, &num) != 3) {
        return 1;
    }
    if (isInSequence(a, d, num)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}