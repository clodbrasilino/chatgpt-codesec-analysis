#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int maxDivisorInInterval(int start, int end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }

    int *divisors = (int *)calloc(end - start + 1, sizeof(int));
    for (int i = start; i <= end; ++i) {
        divisors[i - start] = 1;
    }

    for (int i = 2; i <= end / 2; ++i) {
        if (divisors[i - start] != 1)
            continue;
        for (int j = i * 2; j <= end; j += i) {
            if (j >= start && j <= end && divisors[j - start] == 1) {
                divisors[j - start] = i;
            }
        }
    }

    int maxDivisor = 1;
    int maxCount = 0;
    int currentCount = 0;

    for (int i = 2; i <= end; ++i) {
        currentCount = 0;
        for (int j = 0; j <= end - start; ++j) {
            if (divisors[j] == i) {
                currentCount++;
            }
        }
        if (currentCount > maxCount) {
            maxCount = currentCount;
            maxDivisor = i;
        }
    }

    free(divisors);
    return maxDivisor;
}

int main() {
    int start, end;
    printf("Enter the start and end of the interval: ");
    scanf("%d %d", &start, &end);

    int result = maxDivisorInInterval(start, end);
    printf("The maximum occurring divisor in the interval is: %d\n", result);

    return 0;
}