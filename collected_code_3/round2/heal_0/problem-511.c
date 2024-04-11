#include <stdio.h>
#include <limits.h>

int minSumOfFactors(int n) {
    if (n == 1)
        return 1;
    int sum = INT_MAX;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int other_factor = n / i;
            if (i == other_factor)
                sum = i < sum ? i : sum;
            else
                sum = (i + other_factor) < sum ? (i + other_factor) : sum;
        }
    }
    return sum == INT_MAX ? (n + 1) : sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Minimum sum of factors: %d\n", minSumOfFactors(num));
    return 0;
}