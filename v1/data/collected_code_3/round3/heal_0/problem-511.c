#include <stdio.h>
#include <math.h>

int minSumOfFactors(int n) {
    if (n == 1)
        return 1;
    int sum = n;
    int i;
    for (i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            sum += i;
            n /= i;
        }
    }
    if (n > 1)
        sum += n;
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Minimum sum of factors: %d\n", minSumOfFactors(num));
    return 0;
}