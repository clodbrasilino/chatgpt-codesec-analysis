#include <stdio.h>

int highestPowerOf2(int num) {
    int power = 0;
    while (num > 1) {
        num /= 2;
        power++;
    }
    return power;
}

int main() {
    int num = 0; 
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Highest power of 2 less than or equal to %d is %d\n", num, highestPowerOf2(num));
    return 0;
}