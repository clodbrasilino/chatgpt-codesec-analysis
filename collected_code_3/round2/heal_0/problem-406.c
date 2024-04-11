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
    printf("Parity of %d is %s", num, (findParity(num) ? "odd" : "even"));
    return 0;
}