#include <stdio.h>

int sumOfEvenFactors(int n) {
    int sum = 0;
    for (int i = 2; i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Sum of even factors: %d\n", sumOfEvenFactors(num));
    return 0;
}