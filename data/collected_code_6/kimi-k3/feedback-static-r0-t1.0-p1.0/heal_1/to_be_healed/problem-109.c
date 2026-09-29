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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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