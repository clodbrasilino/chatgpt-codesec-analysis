#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(int num) {
    if (num < 0) return false;
    if (num == 0) return true;
    
    int original = num;
    int reversed = 0;
    
    while (num > 0) {
        int digit = num % 10;
        if (reversed > (INT_MAX - digit) / 10) return false;
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    
    return original == reversed;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int largest_palindrome(int arr[], int size) {
    if (arr == NULL || size <= 0) return -1;
    
    int largest = -1;
    bool found = false;
    
    for (int i = 0; i < size; i++) {
        if (is_palindrome(arr[i])) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = true;
            }
        }
    }
    
    return found ? largest : -1;
}

int main(void) {
    int arr1[] = {121, 12321, 456, 98989, 1001};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = largest_palindrome(arr1, size1);
    printf("Largest palindrome: %d\n", result1);
    
    int arr2[] = {123, 456, 789};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = largest_palindrome(arr2, size2);
    printf("Largest palindrome: %d\n", result2);
    
    int arr3[] = {-121, -5, 0, 11, 22};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = largest_palindrome(arr3, size3);
    printf("Largest palindrome: %d\n", result3);
    
    return 0;
}