#include <stdio.h>

int demloNumber(int num) {
    int sum = 0;
    for (int i = 1; i < num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    int demlo = demloNumber(number);
    printf("Demlo number for %d is %d\n", number, demlo);
    return 0;
}