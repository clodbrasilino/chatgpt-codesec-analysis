#include<stdio.h>

int isLucid(int num) {
    int sum = 0;

    while (num > 0) {
        int digit = num % 10;
        sum += digit;
        num /= 10;
    }

    if (sum % 4 == 0 || sum % 7 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int getLucidNumber(int n) {

    for (int i = n - 1; i >= 1; i--) {
        if (isLucid(i)) {
            return i;
        }
    }

    return -1; 
}

int main() {
    int n = 0;

    printf("Enter a number: ");
    scanf("%d", &n);

    int lucid = getLucidNumber(n);

    printf("Largest lucid number smaller than or equal to %d is %d\n", n, lucid);

    return 0;
}