#include <stdio.h>

int findFirstDigit(int number) {
    while(number >= 10) {
        number /= 10;
    }
    return number;
}

int main() {
    int number = 0;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    int firstDigit = findFirstDigit(number);
    printf("First digit: %d\n", firstDigit);
    
    return 0;
}