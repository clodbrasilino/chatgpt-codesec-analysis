#include <stdio.h>
#include <math.h>
#include <limits.h>

int sum_even_factors(int n) {
    if (n <= 0) return 0;
    if (n % 2 != 0) return 0;

    long long sum = 0;
    int temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    if (temp == 1) {
        sum -= 2;
    } else {
        sum += 2;
    }

    int limit = (int)sqrt((double)n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            int counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) {
                if (sum > LLONG_MAX - counterpart) {
                    sum = LLONG_MAX;
                } else {
                    sum += counterpart;
                }
            }
        }
    }

    if (n != 2) {
        if (sum > LLONG_MAX - n) {
            sum = LLONG_MAX;
        } else {
            sum += n;
        }
    }
    
    return (int)(sum > INT_MAX ? INT_MAX : sum);
}

int main(void) {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("Sum of even factors: %d\n", sum_even_factors(number));
    return 0;
}