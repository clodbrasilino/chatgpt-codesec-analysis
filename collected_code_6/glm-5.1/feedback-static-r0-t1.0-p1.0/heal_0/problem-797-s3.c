#include <stdio.h>

int sum_odd_natural_numbers(int l, int r) {
    if (l <= 0) {
        l = 1;
    }
    if (r < l) {
        return 0;
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
    int n = ((r - l) / 2) + 1;
    return n * (l + r) / 2;
}

int main() {
    int l, r;
    if (scanf("%d %d", &l, &r) != 2) {
        return 1;
    }
    int result = sum_odd_natural_numbers(l, r);
    printf("%d\n", result);
    return 0;
}