#include <stdio.h>
#include <stdbool.h>

bool isNonPrime(int num) {
    if(num <= 1) {
        return true;
    }
    for(int i = 2; i*i <= num; i++) {
        if(num % i == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(isNonPrime(num)) {
        printf("%d is a non-prime number.\n", num);
    } else {
        printf("%d is a prime number.\n", num);
    }

    return 0;
}