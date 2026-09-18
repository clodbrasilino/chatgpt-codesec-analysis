#include<stdio.h>

unsigned long long factorial(unsigned int num) {
    unsigned long long fact = 1;
    for(unsigned int i = 1; i <= num; ++i)
        fact *= i;
    return fact;
}

unsigned int find_number(unsigned long long x) {
    unsigned int num = 1;
    while(1) {
        if(factorial(num) % x == 0)
            return num;
        num++;
    }
}

int main() {
    unsigned long long x;
    printf("Enter the number x: ");
    scanf("%llu", &x);

    unsigned int result = find_number(x);

    printf("The first natural number whose factorial is divisible by %llu is: %u\n", x, result);
    return 0;
}