#include <stdio.h>
#include <string.h>

int isPalindrome(char str[]) {
    int l = 0;
    int h = strlen(str) - 1;
    while (h > l) {
        if (str[l++] != str[h--]) {
            return 0;
        }
    }
    return 1;
}

void findPalindromes(char *arr[], int n) {
    for(int i=0; i<n; i++) {
        if(isPalindrome(arr[i])) {
            printf("%s ", arr[i]);
        }
    }
}

int main() {
    char *arr[] = {"hello", "madam", "world", "radar", "apple", "bob"};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Palindromes are: ");
    findPalindromes(arr, n);
    return 0;
}