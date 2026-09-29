#include <stdio.h>
#include <string.h>

void findNextPalindrome(char* num) {
    int len = strlen(num);
    int mid = len / 2;
    int left = mid - 1;
    int right = (len % 2) ? mid + 1 : mid;
    int isLeftSmaller = 0;

    while (left >= 0 && num[left] == num[right]) {
        left--;
        right++;
    }

    if (left < 0 || num[left] < num[right]) {
        isLeftSmaller = 1;
    }

    while (left >= 0) {
        num[right++] = num[left--];
    }

    if (isLeftSmaller) {
        int carry = 1;
        left = mid - 1;

        if (len % 2 == 1) {
            num[mid] += carry;
            carry = num[mid] / 10;
            num[mid] %= 10;
            right = mid + 1;
        } else {
            right = mid;
        }

        while (left >= 0) {
            num[left] += carry;
            carry = num[left] / 10;
            num[left] %= 10;
            num[right++] = num[left--];
        }
    }
}

int main() {
    char num[100];
    printf("Enter a number: ");
    scanf("%s", num);
    findNextPalindrome(num);
    printf("Next palindrome is: %s\n", num);
    return 0;
}