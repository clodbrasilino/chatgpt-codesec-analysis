#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

bool is_palindrome(long long n) {
    if (n < 0) {
        return false;
    }
    
    long long original = n;
    long long reversed = 0;
    
    while (n > 0) {
        int digit = n % 10;
        
        if (reversed > (LLONG_MAX - digit) / 10) {
            return false;
        }
        
        reversed = reversed * 10 + digit;
        n /= 10;
    }
    
    return original == reversed;
}

long long find_previous_palindrome(long long n) {
    if (n <= 0) {
        return -1;
    }
    
    if (n == 1) {
        return 0;
    }
    
    for (long long candidate = n - 1; candidate >= 0; candidate--) {
        if (is_palindrome(candidate)) {
            return candidate;
        }
    }
    
    return -1;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char *endptr;
    long long number;
    size_t len;
    
    printf("Enter a number: ");
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    buffer[BUFFER_SIZE - 1] = '\0';
    
    len = strnlen(buffer, BUFFER_SIZE);
    if (len == BUFFER_SIZE - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    number = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }
    
    long long result = find_previous_palindrome(number);
    
    if (result == -1) {
        printf("No previous palindrome exists for %lld\n", number);
    } else {
        printf("Previous palindrome of %lld is %lld\n", number, result);
    }
    
    return EXIT_SUCCESS;
}