#include <stdio.h>

int sum_of_odd_numbers(int l, int r) {
    if (l > r) {
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

    int n = (r - l) / 2 + 1;
    return n * (l + r) / 2;
}

int main(void) {
    int l, r;
    printf("Enter the range l and r: ");
    if (scanf("%d %d", &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%d, %d] = %d\n", l, r, result);

    return 0;
}