#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int is_smart_number(int num)
{
    int factor_count = 0;
    int i;

    if (num <= 0) {
        return 0;
    }

    for (i = 1; i <= num / i; i++) {
        if (num % i == 0) {
            if (i == num / i) {
                factor_count++;
            } else {
                factor_count += 2;
            }
        }
    }

    return (factor_count % 2 != 0);
}

int find_nth_smart_number(int n)
{
    int count = 0;
    int num = 1;

    if (n <= 0) {
        return -1;
    }

    while (count < n) {
        if (num == INT_MAX) {
            return -1;
        }
        if (is_smart_number(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        num++;
    }

    return -1;
}

int main(void)
{
    int n;
    int result;

    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = find_nth_smart_number(n);
    if (result == -1) {
        fprintf(stderr, "Error: Could not find the %dth smart number\n", n);
        return EXIT_FAILURE;
    }

    printf("The %dth smart number is: %d\n", n, result);

    return EXIT_SUCCESS;
}