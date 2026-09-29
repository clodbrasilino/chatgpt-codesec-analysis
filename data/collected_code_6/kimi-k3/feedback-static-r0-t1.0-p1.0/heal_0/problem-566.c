#include <stdio.h>
#include <limits.h>

int sumDigits(unsigned int n)
{
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(void)
{
    unsigned int num = 12345;
    int result = sumDigits(num);
    printf("Sum of digits: %d\n", result);
    return 0;
}