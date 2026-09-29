#include <stdio.h>
#include <stdbool.h>

bool isUndulating(int n) {
    int lastDigit = -1, secondLastDigit = -1;
    while (n > 0) {
        if (lastDigit == -1) {
            lastDigit = n % 10;
        } else if (secondLastDigit == -1) {
            secondLastDigit = n % 10;
            if (secondLastDigit == lastDigit) {
                return false;
            }
        } else {
            if (n % 10 != secondLastDigit) {
                return false;
            }
            secondLastDigit = lastDigit;
            lastDigit = n % 10;
        }
        n /= 10;
    }
    return true;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isUndulating(num)) {
        printf("The number is undulating\n");
    } else {
        printf("The number is not undulating\n");
    }
    return 0;
}