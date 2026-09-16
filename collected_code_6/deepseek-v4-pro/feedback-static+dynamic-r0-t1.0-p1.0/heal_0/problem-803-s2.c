#include <stdio.h>

int is_perfect_square(int num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0 || num == 1) {
        return 1;
    }
    long long left = 1;
    long long right = num / 2;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long square = mid * mid;
        if (square == num) {
            return 1;
        }
        if (square < num) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

int main(void) {
    int numbers[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 2, 3, 5, 10, 15, 99, 101, -1, -16};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < count; i++) {
        if (is_perfect_square(numbers[i])) {
            printf("%d is a perfect square\n", numbers[i]);
        } else {
            printf("%d is not a perfect square\n", numbers[i]);
        }
    }
    
    return 0;
}