#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 32
#define MAX_ALLOWED_VALUE 1000

unsigned long long sum_of_fourth_powers(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long fourth = (unsigned long long)i * i * i * i;
        unsigned long long prev = sum;
        sum += fourth;
        if (sum < prev) {
            return ULLONG_MAX;
        }
    }
    return sum;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE] = {0};
    int c;
    size_t i = 0;
    
    printf("Enter a natural number: ");
    
    while (i < sizeof(input) - 1) {
        c = getchar();
        if (c == EOF) {
            if (ferror(stdin)) {
                fprintf(stderr, "Error reading input\n");
                return 1;
            }
            break;
        }
        if (c == '\n') {
            break;
        }
        if (i < sizeof(input) - 1) {
            input[i++] = (char)c;
        }
    }
    input[i] = '\0';
    
    if (c != '\n' && c != EOF) {
        int discard;
        while ((discard = getchar()) != '\n' && discard != EOF) {
        }
        fprintf(stderr, "Invalid input. Input too long.\n");
        return 1;
    }
    
    if (i == 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    
    for (size_t j = 0; j < i; j++) {
        if (input[j] < '0' || input[j] > '9') {
            fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
            return 1;
        }
    }
    
    char *endptr;
    errno = 0;
    unsigned long long value = strtoull(input, &endptr, 10);
    
    if (errno == ERANGE || value > MAX_ALLOWED_VALUE) {
        fprintf(stderr, "Invalid input. Number out of range (0-%d).\n", MAX_ALLOWED_VALUE);
        return 1;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    
    int n = (int)value;
    unsigned long long result = sum_of_fourth_powers(n);
    
    if (result == ULLONG_MAX) {
        fprintf(stderr, "Overflow occurred during calculation.\n");
        return 1;
    }
    
    printf("Sum of fourth powers from 1 to %d: %llu\n", n, result);
    
    return 0;
}