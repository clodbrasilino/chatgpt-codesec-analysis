#include <stdio.h>
#include <stdbool.h>

bool is_divisible_by_its_digits(int num) {
    int original_num = num;
    while (num > 0) {
        int digit = num % 10;
        if (digit == 0 || original_num % digit != 0) {
            return false;
        }
        num /= 10;
    }
    return true;
}

void find_special_numbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (is_divisible_by_its_digits(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int start = 1;
    int end = 100;
    find_special_numbers(start, end);
    return 0;
}