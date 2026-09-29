#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

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
    char *input = NULL;
    size_t input_size = 0;
    ssize_t len;
    long decimal;
    
    printf("Enter an octal number: ");
    
    len = getline(&input, &input_size, stdin);
    
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
        fprintf(stderr, "Invalid octal number\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (octal_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    printf("Decimal: %ld\n", decimal);
    
    free(input);
    return EXIT_SUCCESS;
}