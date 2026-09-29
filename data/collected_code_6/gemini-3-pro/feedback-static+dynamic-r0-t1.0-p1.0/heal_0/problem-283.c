#include <stdio.h>
#include <stdbool.h>

bool checkDigitFrequency(long long n) {
    if (n < 0) {
        n = -n;
    }

    int freq[10] = {0};
    
    if (n == 0) {
        freq[0] = 1;
    } else {
        while (n > 0) {
            freq[n % 10]++;
            n /= 10;
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (freq[i] > i) {
            return false;
        }
    }

    return true;
}

int main(void) {
    long long testCases[] = {122333, 2033, 10, 0, -122333, 11223344};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; ++i) {
        if (checkDigitFrequency(testCases[i])) {
            printf("%lld: Valid\n", testCases[i]);
        } else {
            printf("%lld: Invalid\n", testCases[i]);
        }
    }

    return 0;
}