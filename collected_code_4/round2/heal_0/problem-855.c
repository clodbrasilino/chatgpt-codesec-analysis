#include <stdio.h>

int checkEvenParity(int num) {
    int count = 0;
    while (num) {
        if (num & 1)
            count++;
        num >>= 1;
    }
    return (count % 2 == 0) ? 1 : 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    if(scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 0;
    }
    if(checkEvenParity(num))
        printf("Number has even parity\n");
    else
        printf("Number has odd parity\n");
    return 0;
}