#include <stdio.h>

int checkFrequency(int num) {
    int count[10] = {0};
    int digit;

    while (num > 0) {
        digit = num % 10;
        count[digit]++;
        num /= 10;
    }

    for (int i = 0; i < 10; i++) {
        if (count[i] > i) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (checkFrequency(num)) {
        printf("Frequency of each digit is less than or equal to the digit itself.\n");
    } else {
        printf("Frequency of at least one digit is greater than the digit itself.\n");
    }

    return 0;
}