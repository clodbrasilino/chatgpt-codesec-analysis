#include <stdio.h>
#include <stdbool.h>

bool checkNumber(int num) {
    int temp = num, digit;
    while (temp) {
        digit = temp % 10;
        if (digit == 0 || num % digit != 0)
            return false;
        temp /= 10;
    }
    return true;
}

void findNumbers(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (checkNumber(i))
            printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int start = 1, end = 100;
    findNumbers(start, end);
    return 0;
}