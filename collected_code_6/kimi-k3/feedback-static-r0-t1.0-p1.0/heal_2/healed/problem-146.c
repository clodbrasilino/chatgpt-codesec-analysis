#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int calculate_ascii_sum(const char *str) {
    int sum = 0;
    size_t i;
    
    if (str == NULL) {
        return -1;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (sum > INT_MAX - (int)(unsigned char)str[i]) {
            return -1;
        }
        sum += (int)(unsigned char)str[i];
    }
    
    return sum;
}

int main(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t len;
    int result;
    
    printf("Enter a string: ");
    
    len = getline(&input, &size, stdin);
    
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    result = calculate_ascii_sum(input);
    
    free(input);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid string\n");
        return 1;
    }
    
    printf("Total ASCII value: %d\n", result);
    
    return 0;
}