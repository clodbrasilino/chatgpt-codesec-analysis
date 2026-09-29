#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool can_be_sum_of_two_squares(int n) {
    if (n < 0) {
        return false;
    }
    long long limit = (long long)sqrt(n);
    for (long long a = 0; a <= limit; a++) {
        long long b_squared = n - a * a;
        long long b = (long long)sqrt(b_squared);
        if (b * b == b_squared) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int num;
    if (scanf("%d", &num) == 1) {
        if (can_be_sum_of_two_squares(num)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        return 0;
    }
    return 1;
}