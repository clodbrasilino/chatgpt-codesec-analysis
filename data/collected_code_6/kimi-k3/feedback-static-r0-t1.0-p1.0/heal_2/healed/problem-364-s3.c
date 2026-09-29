#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countFlips(const char *str, size_t len) {
    if (str == NULL) {
        return -1;
    }
    
    if (len == 0) {
        return 0;
    }
    
    int count1 = 0;
    int count2 = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }
        
        char expected1 = (i % 2 == 0) ? '0' : '1';
        char expected2 = (i % 2 == 0) ? '1' : '0';
        
        if (str[i] != expected1) {
            count1++;
        }
        if (str[i] != expected2) {
            count2++;
        }
    }
    
    return (count1 < count2) ? count1 : count2;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    
    printf("Enter binary string: ");
    
    len = getline(&buffer, &buffer_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    int result = countFlips(buffer, (size_t)len);
    if (result < 0) {
        fprintf(stderr, "Invalid input: not a binary string\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    printf("Number of flips required: %d\n", result);
    
    free(buffer);
    return EXIT_SUCCESS;
}