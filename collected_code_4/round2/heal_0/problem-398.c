#include <stdio.h>

int sum_of_digits(int num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void digits_sum_list(int *list, int length) {
    for (int i=0; i<length; i++) {
        printf("The sum of digits for %d is %d\n", list[i], sum_of_digits(list[i]));
    }
}

int main() {
    int list[] = {123, 456, 789, 321};
    int length = sizeof(list)/sizeof(list[0]);

    digits_sum_list(list, length);

    return 0;
}