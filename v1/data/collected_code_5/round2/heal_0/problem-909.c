#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool isPalindrome(int number) {
    char str[20];
    sprintf(str, "%d", number);

    int len = strlen(str);
    for (int i=0; i<len/2; i++)
        if (str[i] != str[len-1-i])
            return false;
    return true;
}

int findPrevPalindrome(int number) {
    for (int i=number-1; i > 0; i--)
        if (isPalindrome(i))
            return i;
    return -1;
}

int main(){
    int number, palindrome;
    printf("\nEnter a number : ");
    scanf("%d",&number);

    palindrome = findPrevPalindrome(number);
    if (palindrome != -1)
        printf("\nPrevious palindrome is : %d", palindrome);
    else
        printf("\nNo previous palindrome found");

    return 0;
}