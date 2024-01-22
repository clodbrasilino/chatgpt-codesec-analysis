#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_INPUT_LENGTH 101

void reverse(char* str, const size_t len) {
    size_t i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void incrementMid(char* num, const size_t len) {
    size_t mid = len / 2;
    int carry = 1;
    int i;
    for (i = mid - 1; i >= 0 && i < len; i--) {
        int digit = (num[i] - '0') + carry;
        carry = digit / 10;
        num[i] = (digit % 10) + '0';
    }
}

void findNextPalindrome(char* num) {
    if(num != NULL) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        size_t len = strlen(num);
        if(len > 0) {
           size_t mid = len / 2;
           size_t i;
           for (i = 0; i < mid; i++) {
               if (num[i] != num[len - 1 - i]) break;
           }

           if (i != mid || len % 2 == 1) incrementMid(num, len);
           for (i = mid; i < len; i++) num[i] = num[len - 1 - i];
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char num[MAX_INPUT_LENGTH] = {0};
    printf("Enter a number: ");
    if(fgets(num, MAX_INPUT_LENGTH - 1, stdin)) {
        num[strcspn(num, "\n")] = '\0';
        findNextPalindrome(num);
        printf("Next smallest palindrome: %s\n", num);
    } else {
        printf("Failed to read the input\n");
    }
    return 0;
}