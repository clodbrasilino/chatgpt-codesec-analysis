#include <stdio.h>
#include <stdbool.h>

static bool is_abundant(unsigned long n)
{
    unsigned long sum;
    unsigned long i;

    if (n < 2UL) {
        return false;
    }

    sum = 1UL;
    for (i = 2UL; i * i <= n; i++) {
        if (n % i == 0UL) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum > n;
}

int main(void)
{
    unsigned long number;
    int result;

    printf("Enter a positive integer: ");
    result = scanf("%lu", &number);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    if (is_abundant(number)) {
        printf("%lu is abundant\n", number);
    } else {
        printf("%lu is not abundant\n", number);
    }

    return 0;
}