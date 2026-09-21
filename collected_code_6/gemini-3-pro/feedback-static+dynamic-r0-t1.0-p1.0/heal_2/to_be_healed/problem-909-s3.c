#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(long long num) {
    if (num < 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[64];
    snprintf(str, sizeof(str), "%lld", num);
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    
    return 1;
}

long long get_previous_palindrome(long long num) {
    if (num <= 0) {
        return -1;
    }
    
    long long current = num - 1;
    
    while (current >= 0) {
        if (is_palindrome(current)) {
            return current;
        }
        current--;
    }
    
    return -1;
}

int main(void) {
    long long input = 0;
    
    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = get_previous_palindrome(input);
    
    if (result == -1) {
        fprintf(stderr, "No previous palindrome found\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}