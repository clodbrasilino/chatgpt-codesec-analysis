#include <stdio.h>
#include <string.h>

void generateNextPalindrome(char *num, int n) {
    int mid = n / 2;
    int left = mid - 1;
    int right = (n % 2) ? mid + 1 : mid;
    int i = left, j = right;
    while (i >= 0 && num[i] == num[j]) {
        i--, j++;
    }
    if (i < 0 || num[i] < num[j]) {
        i = left, j = right;
        if (n % 2 == 0) {
            num[mid]++;
            num[mid + 1] = num[mid];
        } else {
            num[mid]++;
        }
        while (i >= 0) {
            num[j] = num[i];
            j++, i--;
        }
    } else {
        while (i >= 0) {
            num[j] = num[i];
            j++, i--;
        }
    }
}

int nextSmallestPalindrome(int num) {
    char strNum[16];
    sprintf(strNum, "%d", num);
    int len = strlen(strNum);
    generateNextPalindrome(strNum, len);
    int palindrome;
    sscanf(strNum, "%d", &palindrome);
    return palindrome;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Next smallest palindrome: %d\n", nextSmallestPalindrome(num + 1));
    return 0;
}