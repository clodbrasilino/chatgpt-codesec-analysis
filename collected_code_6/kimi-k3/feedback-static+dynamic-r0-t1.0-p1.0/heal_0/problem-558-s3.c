#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int digit_distance(int a, int b)
{
    int distance = 0;
    long long abs_a = llabs((long long)a);
    long long abs_b = llabs((long long)b);

    if (abs_a == 0 && abs_b == 0)
    {
        return 0;
    }

    while (abs_a > 0 || abs_b > 0)
    {
        int digit_a = (int)(abs_a % 10);
        int digit_b = (int)(abs_b % 10);
        distance += abs(digit_a - digit_b);
        abs_a /= 10;
        abs_b /= 10;
    }

    return distance;
}

int main(void)
{
    int num1 = 123;
    int num2 = 456;
    int result = digit_distance(num1, num2);
    printf("Digit distance between %d and %d: %d\n", num1, num2, result);

    num1 = -123;
    num2 = 123;
    result = digit_distance(num1, num2);
    printf("Digit distance between %d and %d: %d\n", num1, num2, result);

    num1 = 0;
    num2 = 0;
    result = digit_distance(num1, num2);
    printf("Digit distance between %d and %d: %d\n", num1, num2, result);

    return 0;
}