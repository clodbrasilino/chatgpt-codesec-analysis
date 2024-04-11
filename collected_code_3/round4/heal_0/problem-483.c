#include <stdio.h>

unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for(int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int findNumber(int x) {
    int i = 1;
    while(1) {
        if(factorial(i) % x == 0) {
            return i;
        }
        i++;
    }
}

int main() {
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    printf("The first natural number whose factorial is divisible by %d is %d\n", x, findNumber(x));
    return 0;
}