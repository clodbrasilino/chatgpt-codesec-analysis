#include <stdio.h>

int find_parity(int num) {
    int parity = 0;
    while (num) {
        parity ^= 1;
        num &= (num - 1);
    }
    return parity;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int result = find_parity(number);
    if (result == 0) {
        printf("Even parity\n");
    } else {
        printf("Odd parity\n");
    }
    return 0;
}