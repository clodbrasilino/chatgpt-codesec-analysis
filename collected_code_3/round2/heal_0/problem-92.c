#include <stdio.h>
#include <stdbool.h>

bool isUndulating(int n) {
    int digit1, digit2;
    if(n < 100) return false;
    digit1 = n % 10;
    n /= 10;
    digit2 = n % 10;
    if(digit1 == digit2) return false;
    while(n) {
        if(n % 10 != digit1) return false;
        n /= 10;
        if(!n) break;
        if(n % 10 != digit2) return false;
        n /= 10;
    }
    return true;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isUndulating(num)) {
        printf("The number is undulating\n");
    } else {
        printf("The number is not undulating\n");
    }
    return 0;
}