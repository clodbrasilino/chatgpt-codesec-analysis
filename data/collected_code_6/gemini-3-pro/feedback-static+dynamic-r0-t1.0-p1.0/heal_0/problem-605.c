#include <stdio.h>
#include <stdbool.h>

bool is_prime(int number);

bool is_prime(int number) {
    if (number <= 1) {
        return false;
    }
    if (number == 2 || number == 3) {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }
    
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int test_numbers[] = {-10, 0, 1, 2, 3, 4, 17, 25, 997, 1000};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (is_prime(test_numbers[i])) {
            printf("%d is prime\n", test_numbers[i]);
        } else {
            printf("%d is not prime\n", test_numbers[i]);
        }
    }

    return 0;
}