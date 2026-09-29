#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(long num) {
    long original = num, reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return original == reversed;
}

long previous_palindrome(long num) {
    if (num <= 10) {
        return -1; // No palindrome exists before 10
    }
    num--;
    while (!is_palindrome(num)) {
        num--;
    }
    return num;
}

int main() {
    long test_num = 123456;
    long result = previous_palindrome(test_num);
    if (result != -1) {
        printf("The previous palindrome of %ld is %ld\n", test_num, result);
    } else {
        printf("No previous palindrome found for %ld\n", test_num);
    }
    return 0;
}