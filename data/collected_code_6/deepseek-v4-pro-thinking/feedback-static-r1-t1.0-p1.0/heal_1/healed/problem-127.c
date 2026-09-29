#include <stdio.h>

long long multiply(int a, int b) {
    int sign = ((a < 0) ^ (b < 0)) ? -1 : 1;
    unsigned long long ua = a < 0 ? (unsigned long long)(-(long long)a) : (unsigned long long)a;
    unsigned long long ub = b < 0 ? (unsigned long long)(-(long long)b) : (unsigned long long)b;
    unsigned long long result = 0;

    while (ub > 0) {
        if (ub & 1ULL) {
            result += ua;
        }
        ua <<= 1;
        ub >>= 1;
    }

    return sign < 0 ? -(long long)result : (long long)result;
}

int main(void) {
    printf("%lld\n", multiply(12, 13));
    printf("%lld\n", multiply(-5, 7));
    printf("%lld\n", multiply(0, -3));
    return 0;
}