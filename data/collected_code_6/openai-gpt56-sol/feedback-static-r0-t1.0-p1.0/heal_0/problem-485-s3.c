#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_palindrome(int value)
{
    if (value < 0) {
        return false;
    }

    int original = value;
    int reversed = 0;

    do {
        reversed = reversed * 10 + value % 10;
        value /= 10;
    } while (value != 0);

    return original == reversed;
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
    int array[] = {121, 34, 898, 12321, 678, 44, 1001};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int largest = 0;

    if (!find_largest_palindrome(array, length, &largest)) {
        if (fputs("No palindromic number found.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", largest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}