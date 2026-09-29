#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_palindrome(int value)
{
    if (value < 0) {
        return false;
    }

    int original = value;
    int reversed = 0;

    do {
        int digit = value % 10;

        if (reversed > (INT_MAX - digit) / 10) {
            return false;
        }

        reversed = reversed * 10 + digit;
        value /= 10;
    } while (value != 0);

    return reversed == original;
}

static bool find_largest_palindrome(const int array[], size_t length, int *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return false;
    }

    bool found = false;
    int largest = 0;

    for (size_t i = 0U; i < length; ++i) {
        if (is_palindrome(array[i]) && (!found || array[i] > largest)) {
            largest = array[i];
            found = true;
        }
    }

    if (found) {
        *result = largest;
    }

    return found;
}

int main(void)
{
    const int numbers[] = {121, 45, 1331, 10, 989, -22, 0, 12321};
    const size_t length = sizeof numbers / sizeof numbers[0];
    int largest = 0;

    if (!find_largest_palindrome(numbers, length, &largest)) {
        if (fputs("No palindromic number found.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (printf("%d\n", largest) < 0) {
        return 1;
    }

    return 0;
}