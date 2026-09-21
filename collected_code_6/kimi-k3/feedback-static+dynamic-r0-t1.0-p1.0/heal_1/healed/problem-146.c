#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculate_ascii_sum(const char *str) {
    int sum = 0;
    size_t i;
    
    if (str == NULL) {
        return -1;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        sum += (int)(unsigned char)str[i];
    }
    
    return sum;
}

int main(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t nread;
    int result;
    
    printf("Enter a string: ");
    
    nread = getline(&input, &size, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    result = calculate_ascii_sum(input);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid string\n");
        free(input);
        return 1;
    }
    
    printf("Total ASCII value: %d\n", result);
    
    free(input);
    return 0;
}