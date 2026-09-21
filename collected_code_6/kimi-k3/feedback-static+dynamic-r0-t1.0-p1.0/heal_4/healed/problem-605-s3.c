#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    if (num == 2) {
        return true;
    }
    if (num % 2 == 0) {
        return false;
    }
    
    for (int i = 3; i <= num / i; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    char *endptr;
    long value;
    
    printf("Enter an integer: ");
    
    read_len = getline(&buffer, &buffer_size, stdin);
    
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }
    
    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
    }
    
    errno = 0;
    value = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0' || value > INT_MAX || value < INT_MIN) {
        fprintf(stderr, "Invalid input format\n");
        free(buffer);
        return 1;
    }
    
    int num = (int)value;
    
    if (is_prime(num)) {
        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }
    
    free(buffer);
    return 0;
}