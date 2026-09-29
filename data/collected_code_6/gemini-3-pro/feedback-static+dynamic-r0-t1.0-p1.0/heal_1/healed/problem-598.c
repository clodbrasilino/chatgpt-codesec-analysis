#include <stdio.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        count++;
        n /= 10;
    }
    return count;
}

long long intPow(int base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int isArmstrong(int n) {
    if (n < 0) {
        return 0;
    }
    
    int originalNum = n;
    int numDigits = countDigits(n);
    long long sum = 0;
    
    while (n != 0) {
        int remainder = n % 10;
        sum += intPow(remainder, numDigits);
        n /= 10;
    }
    
    return (sum == (long long)originalNum);
}

int main() {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return 1;
    }
    
    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }
    
    return 0;
}