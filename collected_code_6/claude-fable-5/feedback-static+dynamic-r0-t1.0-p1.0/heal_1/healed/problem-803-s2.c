#include <stdio.h>
#include <stdlib.h>

static int is_perfect_square(long long num)
{
    long long low;
    long long high;

    if (num < 0) {
        return 0;
    }
    if (num < 2) {
        return 1;
    }

    low = 1;
    high = num / 2;
    if (high > 3037000499LL) {
        high = 3037000499LL;
    }

    while (low <= high) {
        const long long mid = low + (high - low) / 2;
        const long long sq = mid * mid;
        if (sq == num) {
            return 1;
        } else if (sq < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

int main(void)
{
    long long num;

    printf("Enter a number: ");
    if (scanf("%lld", &num) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (num > 3037000499LL * 3037000499LL) {
        fprintf(stderr, "Number too large.\n");
        return EXIT_FAILURE;
    }

    if (is_perfect_square(num)) {
        printf("%lld is a perfect square.\n", num);
    } else {
        printf("%lld is not a perfect square.\n", num);
    }

    return EXIT_SUCCESS;
}