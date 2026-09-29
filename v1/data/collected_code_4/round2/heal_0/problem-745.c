#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isDivisible(int num) {
    int temp = num, digit;
    while (temp) {
        digit = temp % 10;
        if (digit == 0 || num % digit != 0) {
            return false;
        }
        temp = temp / 10;
    }
    return true;
}

void getNumbers(int from, int to) {
    if(from <= 0 || to <= 0 || from >= to) {
        printf("Invalid range!\n");
        return;
    }
    for (int i = from; i <= to; i++) {
        if (isDivisible(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int from, to;
    printf("Enter a range (two numbers):\n");
    if(scanf("%d %d", &from, &to) != 2) {
        printf("Invalid input! Please enter two integers.\n");
        return 1;
    }
    getNumbers(from, to);
    return 0;
}