#include <stdio.h>
#include <math.h>

int count_divisors(int n)
{
    if (n <= 0) {
        return 0;
    }

    int count = 0;
    int sqrt_n = (int)sqrt((double)n);

    for (int i = 1; i <= sqrt_n; i++) {
        if (n % i == 0) {
            if (i * i == n) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }

    return count;
}

int main(void)
{
    int number;

    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    int result = count_divisors(number);
    printf("Number of divisors: %d\n", result);

    return 0;
}