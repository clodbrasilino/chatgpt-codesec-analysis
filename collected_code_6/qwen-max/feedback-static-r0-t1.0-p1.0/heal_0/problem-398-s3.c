#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

void process_list(int *list, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("Sum of digits of %d is %d\n", list[i], sum_of_digits(list[i]));
    }
}

int main() {
    int numbers[] = {123, 456, 789, 0, -123};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    process_list(numbers, length);
    return 0;
}