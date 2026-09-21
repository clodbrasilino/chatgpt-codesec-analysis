#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_palindrome(int num)
{
    int reversed = 0;
    int original;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;

    if (num < 0) {
        return false;
    }

    original = num;

    while (num > 0) {
        digit = num % 10;
        if (reversed > (2147483647 - digit) / 10) {
            return false;
        }
        reversed = reversed * 10 + digit;
        num /= 10;
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
    int numbers[] = { 123, 121, 45654, 78, 909, 2, 10 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int largest;

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