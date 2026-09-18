#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_palindrome(int n) {
    char str[20];
    snprintf(str, 20, "%d", n);
    int length = strlen(str);
    for(int i = 0; i < length / 2; i++) {
        if(str[i] != str[length - 1 - i]) {
            return false;
        }
    }
    return true;
}

int previous_palindrome(int num) {
    for(int i = num - 1; i > 0; --i) {
        if(is_palindrome(i)) {
            return i;
        }
    }
    return -1;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    int result = previous_palindrome(num);
    if(result != -1) {
        printf("The previous palindrome is %d.\n", result);
    } else {
        printf("No previous palindrome was found.\n");
    }

    return 0;
}