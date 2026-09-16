#include <stdio.h>
#include <limits.h>

int count_digits(int number) {
    int count = 0;
    
    if (number == 0) {
        return 1;
    }
    
    if (number < 0) {
        number = -number;
    }
    
    while (number != 0) {
        number /= 10;
        count++;
    }
    
    return count;
}

int main(void) {
    int test_numbers[] = {0, 5, 123, -456, 10000, INT_MAX, INT_MIN};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Number: %d, Digits: %d\n", test_numbers[i], count_digits(test_numbers[i]));
    }
    
    return 0;
}