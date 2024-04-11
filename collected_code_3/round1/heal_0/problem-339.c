#include <stdio.h>

int maxOccuringDivisor(int l, int r) {
    int maxDivisor = 0;
    int maxCount = 0;

    for (int i = l; i <= r; i++) {
        int count = 0;
        for (int j = 1; j <= i; j++) {
            if (i % j == 0) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxDivisor = i;
        }
    }
    return maxDivisor;
}

int main() {
    int l, r;
    printf("Enter the interval (l, r): ");
    scanf("%d %d", &l, &r);
    int result = maxOccuringDivisor(l, r);
    printf("The number with maximum divisors in the interval is: %d\n", result);
    return 0;
}