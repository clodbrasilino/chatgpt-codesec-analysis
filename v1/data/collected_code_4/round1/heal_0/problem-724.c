#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LENGTH 100

long calculateSum(long base, long power){
    double d = pow((double)base, (double)power);
    long number = (long)d;

    long temp, sum = 0;
    while(number > 0){
        temp = number % 10;
        sum += temp;
        number /= 10;
    }
    return sum;
}

int main(void){
    long base, power;

    printf("Enter base: ");
    if(scanf("%ld", &base) != 1) return 1;

    printf("Enter power: ");
    if(scanf("%ld", &power) != 1) return 1;

    long sum = calculateSum(base, power);

    printf("Sum of all digits of %ld to the power of %ld: %ld\n", base, power, sum);

    return 0;
}