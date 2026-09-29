#include <stdio.h>
#include <stdbool.h>

bool checkDigitFrequencies(long long num) {
    if (num < 0) {
        num = -num;
    }

    int frequencies[10] = {0};
    
    if (num == 0) {
        frequencies[0] = 1;
    } else {
        while (num > 0) {
            int digit = num % 10;
            frequencies[digit]++;
            num /= 10;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (frequencies[i] > i) {
            return false;
        }
    }

    return true;
}

int main() {
    long long test_numbers[] = {122, 333, 11, 0, 4444, 21333, 2333};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; i++) {
        long long num = test_numbers[i];
        bool result = checkDigitFrequencies(num);
        if (result) {
            printf("%lld: Valid\n", num);
        } else {
            printf("%lld: Invalid\n", num);
        }
    }

    return 0;
}