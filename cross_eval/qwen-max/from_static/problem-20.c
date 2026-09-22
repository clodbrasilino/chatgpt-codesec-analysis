#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_woodall_number(unsigned long long n) {
    if (n == 0) return false;
    for (unsigned long long k = 1; (k << k) <= n; ++k) {
        if ((k << k) - k == n) {
            return true;
        }
    }
    return false;
}

int main() {
    unsigned long long num;
    printf("Enter a number: ");
    scanf("%llu", &num);
    if (is_woodall_number(num)) {
        printf("%llu is a Woodall number.\n", num);
    } else {
        printf("%llu is not a Woodall number.\n", num);
    }
    return 0;
}