#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(int num) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int original = num, reversed = 0, remainder;
    if (num < 0) num = -num;
    while (num != 0) {
        remainder = num % 10;
        reversed = reversed * 10 + remainder;
        num /= 10;
    }
    return original == reversed;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int largest_palindrome(int *arr, int size) {
    int max_palindrome = INT_MIN;
    for (int i = 0; i < size; ++i) {
        if (is_palindrome(arr[i]) && arr[i] > max_palindrome) {
            max_palindrome = arr[i];
        }
    }
    return max_palindrome;
}

int main() {
    int arr[] = {123, 121, 134, 789, 898};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = largest_palindrome(arr, size);
    printf("%d\n", result);
    return 0;
}