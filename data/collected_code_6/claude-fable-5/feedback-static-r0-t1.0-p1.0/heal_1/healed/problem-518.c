#include <stdio.h>
#include <stdlib.h>

long long find_square_root(long long num, int *is_perfect)
{
    long long low;
    long long high;

    *is_perfect = 0;

    if (num < 0) {
        return -1;
    }

    if (num == 0 || num == 1) {
        *is_perfect = 1;
        return num;
    }

    low = 1;
    high = num;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long sq;

        if (mid > num / mid) {
            high = mid - 1;
            continue;
        }

        sq = mid * mid;

        if (sq == num) {
            *is_perfect = 1;
            return mid;
        } else if (sq < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main(void)
{
    long long number;
    long long root;
    int is_perfect;
    int result;

    printf("Enter a non-negative integer: ");

    result = scanf("%lld", &number);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number < 0) {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    root = find_square_root(number, &is_perfect);

    if (is_perfect == 1) {
        printf("The square root of %lld is %lld.\n", number, root);
    } else {
        printf("%lld is not a perfect square.\n", number);
    }

    return EXIT_SUCCESS;
}