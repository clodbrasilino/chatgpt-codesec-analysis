#include <stdio.h>
#include <stdbool.h>

bool is_undulating(int num) {
    if (num < 0) {
        num = -num;
    }
    
    if (num < 100) {
        return false;
    }
    
    int last_digit = num % 10;
    int second_last_digit = (num / 10) % 10;
    
    if (last_digit == second_last_digit) {
        return false;
    }
    
    num /= 100;
    
    while (num > 0) {
        int current_digit = num % 10;
        int expected_digit = (last_digit == (num / 10) % 10) ? second_last_digit : last_digit;
        
        if (current_digit != expected_digit) {
            return false;
        }
        
        num /= 10;
    }
    
    return true;
}

int main(void) {
    int test_numbers[] = {121, 1212, 3434, 123, 111, 12121, 5, 99, 1010};
    int size = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (int i = 0; i < size; i++) {
        if (is_undulating(test_numbers[i])) {
            printf("%d is undulating\n", test_numbers[i]);
        } else {
            printf("%d is not undulating\n", test_numbers[i]);
        }
    }
    
    return 0;
}