#include <stdio.h>
#include <math.h>

long long sum_of_even_factors(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int temp = n;
    while (temp % 2 == 0) {
        temp /= 2;
    }
    
    long long sum = 0;
    int limit = (int)sqrt((double)temp);
    
    for (int i = 1; i <= limit; i++) {
        if (temp % i == 0) {
            sum += i;
            if (i != temp / i) {
                sum += temp / i;
            }
        }
    }
    
    if (n % 2 == 0) {
        long long power = 2;
        while (n % (int)power == 0) {
            power *= 2;
        }
        power /= 2;
        return sum * power;
    }
    
    return 0;
}

int main(void) {
    int number;
    
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Sum of even factors: %lld\n", sum_of_even_factors(number));
    
    return 0;
}