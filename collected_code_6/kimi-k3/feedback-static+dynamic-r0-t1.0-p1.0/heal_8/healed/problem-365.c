#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int count_digits(long long number) {
    int count = 0;
    
    if (number == 0) {
        return 1;
    }
    
    if (number < 0) {
        if (number == LLONG_MIN) {
            number = LLONG_MAX;
        } else {
            number = -number;
        }
    }
    
    while (number > 0) {
        number /= 10;
        count++;
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t capacity = 0;
    ssize_t len;
    char *endptr;
    long long number;
    int digits;
    
    len = getline(&input, &capacity, stdin);
    
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input: empty string\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    number = strtoll(input, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    digits = count_digits(number);
    printf("%d\n", digits);
    
    free(input);
    return EXIT_SUCCESS;
}