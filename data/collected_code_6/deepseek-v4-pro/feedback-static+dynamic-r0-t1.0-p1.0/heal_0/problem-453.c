#include <stdio.h>
#include <math.h>

int sum_even_factors(int n) {
    if (n <= 0) return 0;
    if (n % 2 != 0) return 0;

    int sum = 0;
    int temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    sum += 2 * (temp == 1 ? 0 : 1);

    int limit = (int)sqrt((double)n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            if (i % 2 == 0) sum += i;
            int counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) sum += counterpart;
        }
    }

    if (n % 2 == 0 && n != 2) sum += n;
    return sum;
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