#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(int num) {
    if (num < 0) {
        return false;
    }
    int original = num;
    int reversed = 0;
    while (num > 0) {
        int digit = num % 10;
        if (reversed > (INT_MAX - digit) / 10) {
            return false;
        }
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    return original == reversed;
}

int find_largest_palindrome(const int *array, size_t size, bool *found) {
    if (array == NULL || found == NULL) {
        if (found != NULL) {
            *found = false;
        }
        return -1;
    }

    int max_palindrome = -1;
    *found = false;

    for (size_t i = 0; i < size; ++i) {
        if (is_palindrome(array[i])) {
            if (!*found || array[i] > max_palindrome) {
                max_palindrome = array[i];
                *found = true;
            }
        }
    }

    return max_palindrome;
}

int main(void) {
    int array[] = {12, 121, 33, 45, 989, 78};
    size_t size = sizeof(array) / sizeof(array[0]);
    bool found = false;

    int largest = find_largest_palindrome(array, size, &found);

    if (found) {
        printf("%d\n", largest);
    } else {
        printf("No palindromic number found.\n");
    }

    return 0;
}