#include <stdio.h>
#include <stdbool.h>

bool checkDigitFrequencies(long long num) {
    if (num < 0) {
        num = -num;
    }

    int counts[10] = {0};

    if (num == 0) {
        counts[0] = 1;
    } else {
        while (num > 0) {
            int digit = num % 10;
            counts[digit]++;
            num /= 10;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (counts[i] > i) {
            return false;
        }
    }

    return true;
}

int main(void) {
    long long test_numbers[] = {122333, 22, 11, 2333, 4444, 0, 10, -122};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (checkDigitFrequencies(test_numbers[i])) {
            printf("%lld: Valid\n", test_numbers[i]);
        } else {
            printf("%lld: Invalid\n", test_numbers[i]);
        }
    }

    return 0;
}