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

void find_self_dividing_numbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (is_divisible_by_its_digits(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main(void) {
    int start, end;
    printf("Enter the range (start end): ");
    scanf("%d %d", &start, &end);
    if (start > end) {
        return 1;
    }
    find_self_dividing_numbers(start, end);
    return 0;
}