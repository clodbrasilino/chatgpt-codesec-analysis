#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(long long num) {
    char str[32];
    int len, i;
    
    if (num < 0) {
        return 0;
    }
    
    snprintf(str, sizeof(str), "%lld", num);
    len = strlen(str);
    
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    
    return 1;
}

long long find_previous_palindrome(long long num) {
    if (num <= 0) {
        return -1;
    }
    
    num--;
    
    while (num >= 0) {
        if (is_palindrome(num)) {
            return num;
        }
        num--;
    }
    
    return -1;
}

int main(void) {
    long long num;
    long long prev_palindrome;

    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }

    prev_palindrome = find_previous_palindrome(num);

    if (prev_palindrome != -1) {
        printf("%lld\n", prev_palindrome);
    } else {
        printf("-1\n");
    }

    return EXIT_SUCCESS;
}