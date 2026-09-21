#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int countOddRotations(const char *binaryString, size_t maxLength, int *result) {
    size_t length;
    size_t i;
    int count;
    
    if (binaryString == NULL || result == NULL) {
        return -1;
    }
    
    length = strnlen(binaryString, maxLength);
    
    if (length == maxLength) {
        return -1;
    }
    
    if (length == 0) {
        *result = 0;
        return 0;
    }
    
    for (i = 0; i < length; i++) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1;
        }
    }
    
    count = 0;
    
    for (i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            if (count == INT_MAX) {
                return -1;
            }
            count++;
        }
    }
    
    *result = count;
    return 0;
}

int main(void) {
    char buffer[BUFFER_SIZE + 2];
    size_t len;
    int rotations;
    int status;
    
    printf("Enter a binary string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strcspn(buffer, "\n");
    
    if (buffer[len] == '\n') {
        buffer[len] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    status = countOddRotations(buffer, sizeof(buffer), &rotations);
    
    if (status != 0) {
        fprintf(stderr, "Invalid input: string must contain only '0' and '1'\n");
        return EXIT_FAILURE;
    }
    
    printf("Count of rotations with odd value: %d\n", rotations);
    
    return EXIT_SUCCESS;
}