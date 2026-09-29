#include <stdio.h>

long long sum_of_odd_natural_numbers(int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l < 1) {
        l = 1;
    }
    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    return (long long)(l + r) * ((r - l) / 2 + 1) / 2;
}

int main(void) {
    int l, r;
    printf("Enter lower bound: ");
    if (scanf("%d", &l) != 1) {
        return 1;
    }
    printf("Enter upper bound: ");
    if (scanf("%d", &r) != 1) {
        return 1;
    }
    printf("Sum of odd natural numbers in range [%d, %d]: %lld\n", l, r, sum_of_odd_natural_numbers(l, r));
    return 0;
}