#include <stdio.h>
#include <stdbool.h>

bool is_perfect_square(long long num)
{
    if (num < 0) {
        return false;
    }

    if (num == 0) {
        return true;
    }

    long long low = 1;
    long long high = num;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (mid > num / mid) {
            high = mid - 1;
        } else {
            if (mid == num / mid && num % mid == 0) {
                return true;
            }
            low = mid + 1;
        }
    }

    return false;
}

int main(void)
{
    long long number = 0;

    printf("Enter a number: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    if (is_perfect_square(number)) {
        printf("%lld is a perfect square\n", number);
    } else {
        printf("%lld is not a perfect square\n", number);
    }

    return 0;
}