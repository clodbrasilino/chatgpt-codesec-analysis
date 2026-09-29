#include <stdio.h>

int sum_even_in_range(int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (l % 2 != 0) {
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    int n = (r - l) / 2 + 1;
    return n * (l + r) / 2;
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
    int result = sum_even_in_range(l, r);
    printf("Sum of even numbers in range [%d, %d]: %d\n", l, r, result);
    return 0;
}