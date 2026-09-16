#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int countOddRotations(const char *binaryString, int *result) {
    size_t length;
    size_t i;
    int count;
    
    if (binaryString == NULL || result == NULL) {
        return -1;
    }
    
    length = strlen(binaryString);
    
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
    char buffer[1024];
    int rotations;
    int status;
    
    printf("Enter a binary string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    status = countOddRotations(buffer, &rotations);
    
    if (status != 0) {
        fprintf(stderr, "Invalid input: string must contain only '0' and '1'\n");
        return EXIT_FAILURE;
    }
    
    printf("Count of rotations with odd value: %d\n", rotations);
    
    return EXIT_SUCCESS;
}