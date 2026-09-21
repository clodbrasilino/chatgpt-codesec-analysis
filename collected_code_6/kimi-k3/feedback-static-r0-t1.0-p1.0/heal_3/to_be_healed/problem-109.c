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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    int rotations;
    int status;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    
    printf("Enter a binary string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strcspn(buffer, "\n");
    
    if (len == sizeof(buffer) - 1 && buffer[len] != '\n') {
        if (feof(stdin)) {
            buffer[len] = '\0';
        } else {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    } else {
        buffer[len] = '\0';
    }
    
    status = countOddRotations(buffer, sizeof(buffer), &rotations);
    
    if (status != 0) {
        fprintf(stderr, "Invalid input: string must contain only '0' and '1'\n");
        return EXIT_FAILURE;
    }
    
    printf("Count of rotations with odd value: %d\n", rotations);
    
    return EXIT_SUCCESS;
}