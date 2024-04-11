#include <stdio.h>

int findParity(int num) {
    int parity = 0;
    while (num) {
        parity = !parity;
        num = num & (num - 1);
    }
    return parity;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int parity = findParity(num);
    if (parity == 0)
        printf("Parity of %d is even\n", num);
    else
        printf("Parity of %d is odd\n", num);
    return 0;
}