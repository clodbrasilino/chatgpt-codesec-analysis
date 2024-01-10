#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int maxDiff(const char* binaryString, size_t size) {
    int maxDiff = 0, currentDiff = 0;
    int count0 = 0, count1 = 0;
    size_t i = 0;
    
    while (i < size && binaryString[i] != '\0') {
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
    char binaryString[MAX_SIZE];
    printf("Enter a binary string: ");
    if(fgets(binaryString, sizeof(binaryString), stdin)!= NULL)
    {
        binaryString[strcspn(binaryString, "\n")] = 0; /* Remove newline */

        int result = maxDiff(binaryString, sizeof(binaryString));
        printf("Maximum difference between 0s and 1s: %d\n", result);
    }
     
    return 0;
}