#include <stdio.h>

int findParity(int num) {
    int parity = 0;
    
    while (num != 0) {
        parity = !parity;
        num = num & (num - 1);
    }
    
    return parity;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    
    int result = findParity(number);
    printf("Parity of %d is %d\n", number, result);
    
    return 0;
}