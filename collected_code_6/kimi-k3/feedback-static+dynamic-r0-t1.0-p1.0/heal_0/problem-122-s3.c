#include <stdio.h>
#include <stdlib.h>

int is_smart_number(long long num)
{
    if (num <= 0) {
        return 0;
    }
    if (num % 2 == 0) {
        return 0;
    }
    if (num % 3 == 0) {
        return 0;
    }
    if (num % 5 == 0) {
        return 0;
    }
    if (num % 7 == 0) {
        return 0;
    }
    return 1;
}

long long find_nth_smart_number(int n)
{
    if (n <= 0) {
        return -1;
    }
    long long count = 0;
    long long num = 1;
    while (count < n) {
        if (is_smart_number(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        if (num == 1) {
            num = 2;
        } else if (num % 2 == 0) {
            num += 1;
        } else {
            num += 2;
        }
        if (num < 0) {
            return -1;
        }
    }
    return -1;
}

int main(void)
{
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = find_nth_smart_number(n);
    if (result == -1) {
        fprintf(stderr, "Invalid input or overflow occurred\n");
        return EXIT_FAILURE;
    }
    printf("The %dth smart number is: %lld\n", n, result);
    return EXIT_SUCCESS;
}