#include <stdio.h>

int check_odd_parity(int num) {
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
    if (check_odd_parity(num)) {
        printf("The number has odd parity\n");
    } else {
        printf("The number has even parity\n");
    }
    return 0;
}