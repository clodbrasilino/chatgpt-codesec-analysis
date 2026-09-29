#include <stdio.h>

int findParity(unsigned int num) {
    int parity = 0;
    while (num) {
        parity = !parity;
        num = num & (num - 1);
    }
    return parity;
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        printf("Invalid input.\n");
        return 0;
    }

    int result = findParity(num);
    if(result == 1)
        printf("The number is odd\n");
    else
        printf("The number is even\n");
    
    return 0;
}