#include <stdio.h>
#include <stdbool.h>

bool digit_frequency_valid(unsigned long long number)
{
    int counts[10] = {0};

    if (number == 0ULL) {
        counts[0] = 1;
    } else {
        while (number > 0ULL) {
            counts[number % 10ULL]++;
            number /= 10ULL;
        }
    }

    for (int digit = 0; digit < 10; digit++) {
        if (counts[digit] > digit) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    unsigned long long value = 0ULL;

    printf("Enter a non-negative integer: ");
    if (scanf("%llu", &value) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (digit_frequency_valid(value)) {
        printf("Valid: each digit's frequency is <= the digit itself.\n");
    } else {
        printf("Invalid: some digit occurs more times than its value.\n");
    }

    return 0;
}