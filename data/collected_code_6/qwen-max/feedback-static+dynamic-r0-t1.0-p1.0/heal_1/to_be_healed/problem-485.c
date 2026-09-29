#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int original = n, reversed = 0, remainder;
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return original == reversed;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 54545, got <no output>
  *  test case 2 failed: expected 9, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_largest_palindromic(int arr[], int size) {
    int max_palindrome = -1;
    for (int i = 0; i < size; ++i) {
        if (is_palindrome(arr[i]) && arr[i] > max_palindrome) {
            max_palindrome = arr[i];
        }
    }
    return max_palindrome;
}

int main() {
    int arr[] = {123, 121, 13431, 12321, 45654, 78987};
    int size = sizeof(arr) / sizeof(arr[0]);
    int largest_palindrome = find_largest_palindromic(arr, size);
    printf("The largest palindromic number is: %d\n", largest_palindrome);
    return 0;
}