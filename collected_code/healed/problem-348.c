#include <stdio.h>

int countSequences(const int values[], int length, int sequenceLength) {
    int count = 0;
    
    for (int i = 0; i <= length - sequenceLength; i++) {
        int prefixSum = 0;
        int isValidSequence = 1;
        
        for (int j = i; j < i + sequenceLength; j++) {
            prefixSum += values[j];
            
            if (prefixSum < 0) {
                isValidSequence = 0;
                break;
            }
        }
        
        if (isValidSequence) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int values[] = {1, -2, 3, 4, -5, 6};
    int length = sizeof(values) / sizeof(values[0]);
    int sequenceLength = 3;
    
    int numOfSequences = countSequences(values, length, sequenceLength);
    
    printf("Number of sequences: %d\n", numOfSequences);
    
    return 0;
}