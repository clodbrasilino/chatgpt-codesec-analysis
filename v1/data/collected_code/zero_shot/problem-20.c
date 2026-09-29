#include <stdio.h>

int isWoodball(int number) {
    int sum = 0;
    int temp = number;
    
    while (temp > 0) {
        int digit = temp % 10;
        temp /= 10;
        sum += digit;
    }
    
    if (sum % 10 == 0) {
        printf("%d is a woodball number.\n", number);
        return 1;
    }
    else {
        printf("%d is not a woodball number.\n", number);
        return 0;
    }
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    
    isWoodball(number);
    
    return 0;
}