#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_palindrome(int num)
{
    long long reversed = 0;
    long long original;
    long long n;

    if (num < 0) {
        return false;
    }

    original = (long long)num;
    n = original;

    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }

    return (reversed == original);
}

static bool find_largest_palindrome(const int *arr, size_t size, int *result)
{
    bool found = false;
    size_t i;

    if ((arr == NULL) || (result == NULL) || (size == 0U)) {
        return false;
    }

    for (i = 0U; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if ((!found) || (arr[i] > *result)) {
                *result = arr[i];
                found = true;
            }
        }
    }

    return found;
}

int main(void)
{
    int numbers[] = {123, 121, 45654, 98789, 10, 7, 88, -121, 2002};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int largest = 0;

    if (find_largest_palindrome(numbers, count, &largest)) {
        if (printf("Largest palindromic number: %d\n", largest) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No palindromic number found.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}