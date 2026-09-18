#include <stdio.h>

int highestPowerof2(int num) {
    int p = 1;

    while (p <= num) {
        p <<= 1;
    }

    return p >> 1;
}
  
int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int res = highestPowerof2(num);
    printf("The highest power of 2 less than or equal to %d is %d\n", num, res);
    return 0;
}