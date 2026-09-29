#include <stdio.h>
#include <stdbool.h>

static bool is_self_dividing(int number)
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

static int find_self_dividing_in_range(int start, int end, FILE *out)
{
    int count = 0;
    int i;

    if (out == NULL) {
        return -1;
    }

    if (start > end) {
        int tmp = start;
        start = end;
        end = tmp;
    }

    if (start < 1) {
        start = 1;
    }

    for (i = start; i <= end; i++) {
        if (is_self_dividing(i)) {
            if (fprintf(out, "%d\n", i) < 0) {
                return -1;
            }
            count++;
        }
    }

    return count;
}

int main(void)
{
    int start = 1;
    int end = 200;
    int result;

    result = find_self_dividing_in_range(start, end, stdout);

    if (result < 0) {
        fprintf(stderr, "Error while searching or printing results\n");
        return 1;
    }

    if (printf("Found %d numbers in range [%d, %d]\n", result, start, end) < 0) {
        return 1;
    }

    return 0;
}