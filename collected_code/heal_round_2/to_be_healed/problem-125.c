#include <stdio.h>
#include <string.h>

int maxDiff(const char* binaryString) {
    int maxDiff = 0, currentDiff = 0;
    int count0 = 0, count1 = 0;
    size_t i = 0;
    
    while (binaryString[i] != '\0') {
        if (binaryString[i] == '0') {
            count0++;
        } else if (binaryString[i] == '1') {
            count1++;
        }
        
        currentDiff = count0 - count1;
        if (currentDiff > maxDiff) {
            maxDiff = currentDiff;
        }
        
        if (currentDiff < 0) {
            count0 = 0;
            count1 = 0;
        }
        
        i++;
    }
    
    return maxDiff;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char binaryString[100];
    printf("Enter a binary string: ");
    fgets(binaryString, sizeof(binaryString), stdin);
    binaryString[strcspn(binaryString, "\n")] = 0; /* Remove newline */
    
    int result = maxDiff(binaryString);
    printf("Maximum difference between 0s and 1s: %d\n", result);
    
    return 0;
}