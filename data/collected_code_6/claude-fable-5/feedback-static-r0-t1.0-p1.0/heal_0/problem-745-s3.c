#include <stdio.h>
#include <stdbool.h>

static bool is_divisible_by_digits(int number)
{
    int n = number;

    if (n <= 0) {
        return false;
    }

    while (n > 0) {
        int digit = n % 10;

        if (digit == 0) {
            return false;
        }

        if (number % digit != 0) {
            return false;
        }

        n /= 10;
    }

    return true;
}

static int find_divisible_numbers(int start, int end, int *results, size_t max_results)
{
    int count = 0;
    int i;

    if (results == NULL || max_results == 0 || start > end) {
        return 0;
    }

    for (i = start; i <= end; i++) {
        if (is_divisible_by_digits(i)) {
            if ((size_t)count < max_results) {
                results[count] = i;
                count++;
            } else {
                break;
            }
        }
        if (i == end) {
            break;
        }
    }

    return count;
}

int main(void)
{
    int results[1000];
    int start = 1;
    int end = 100;
    int count;
    int i;

    count = find_divisible_numbers(start, end, results, sizeof(results) / sizeof(results[0]));

    if (count == 0) {
        printf("No numbers found in range [%d, %d]\n", start, end);
        return 0;
    }

    printf("Numbers in range [%d, %d] divisible by all their digits:\n", start, end);
    for (i = 0; i < count; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}