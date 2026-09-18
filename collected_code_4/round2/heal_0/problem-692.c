#include <stdio.h>

#define MAX 100001
#define MOD 100

int fact[MAX];

void computeFactorial() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i < MAX; i++)
        fact[i] = (i * fact[i - 1]) % MOD;
}

int getFactorialDigits(int num) {
    if(num >= MAX) return 0;
    return fact[num];
}

int main() {
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    computeFactorial();
    int result = getFactorialDigits(num);
    printf("The last two digits of factorial of %d are %02d\n", num, result);
    return 0;
}