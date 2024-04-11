#include <stdio.h>

int checkOddParity(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count % 2;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (checkOddParity(num)) {
        printf("The number has odd parity.\n");
    } else {
        printf("The number does not have odd parity.\n");
    }
    return 0;
}