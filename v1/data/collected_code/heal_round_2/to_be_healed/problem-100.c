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
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char num[100];
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%99s", num);
    findNextPalindrome(num);
    printf("Next smallest palindrome: %s\n", num);

    return 0;
}