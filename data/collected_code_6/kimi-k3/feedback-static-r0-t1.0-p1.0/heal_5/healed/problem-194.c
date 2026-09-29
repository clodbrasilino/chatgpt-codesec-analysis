#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define MAX_INPUT_LEN 64

int octal_to_decimal(const char *octal_str, long *result) {
    char *endptr;
    long value;
    
    if (octal_str == NULL || result == NULL) {
        return -1;
    }
    
    if (*octal_str == '\0') {
        return -1;
    }
    
    errno = 0;
    value = strtol(octal_str, &endptr, 8);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return -1;
    }
    
    if (endptr == octal_str || *endptr != '\0') {
        return -1;
    }
    
    *result = value;
    return 0;
}

int main(void) {
    char input[MAX_INPUT_LEN];
    long decimal;
    size_t len;
    
    printf("Enter an octal number: ");
    
    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strlen(input);
    
    if (len == MAX_INPUT_LEN - 1 && input[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid octal number\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid octal number\n");
        return EXIT_FAILURE;
    }
    
    if (octal_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return EXIT_FAILURE;
    }
    
    printf("Decimal: %ld\n", decimal);
    
    return EXIT_SUCCESS;
}