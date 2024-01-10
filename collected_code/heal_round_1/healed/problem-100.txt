#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void reverse(char* str, const int len) {
    int i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void incrementMid(char* num, const int len) {
    int mid = len / 2;
    int carry = 1;
    int i;
    for (i = mid - 1; i >= 0; i--) {
        int digit = num[i] - '0' + carry;
        carry = digit / 10;
        num[i] = digit % 10 + '0';
    }
}

void findNextPalindrome(char* num) {
    int len = strlen(num);
    int mid = len / 2;
    int i;
    for (i = 0; i < mid; i++) {
        if (num[i] != num[len - 1 - i]) {
            break;
        }
    }

    if (i != mid || len % 2 == 1) {
        incrementMid(num, len);
    }
  
    for (i = mid; i < len; i++) {
        num[i] = num[len - 1 - i];
    }
}

int main() {
    char num[100];
    printf("Enter a number: ");
    scanf("%99s", num);
    findNextPalindrome(num);
    printf("Next smallest palindrome: %s\n", num);

    return 0;
}