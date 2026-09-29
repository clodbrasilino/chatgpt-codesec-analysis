#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_palindrome(int num)
{
    long long original;
    long long reversed = 0;
    long long n;

    if (num < 0) {
        return false;
    }

    original = (long long)num;
    n = original;

    while (n > 0) {
        reversed = (reversed * 10) + (n % 10);
        n /= 10;
    }

    return reversed == original;
}

static bool find_largest_palindrome(const int *arr, size_t size, int *result)
{
    size_t i;
    bool found = false;
    int largest = 0;

    if (arr == NULL || result == NULL || size == 0) {
        return false;
    }

    for (i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = true;
            }
        }
    }

    if (found) {
        *result = largest;
    }

    return found;
}

int main(void)
{
    int numbers[] = { 123, 121, 45654, 989, 76567, 1000, 44, 7 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int largest = 0;

    if (find_largest_palindrome(numbers, count, &largest)) {
        if (printf("Largest palindromic number: %d\n", largest) < 0) {
            return 1;
        }
    } else {
        if (printf("No palindromic number found.\n") < 0) {
            return 1;
        }
    }

    return 0;
}