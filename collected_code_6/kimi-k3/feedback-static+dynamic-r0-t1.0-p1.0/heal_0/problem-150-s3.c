#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isInSequence(unsigned long long num) {
    if (num == 0) {
        return true;
    }
    
    unsigned long long term = 1;
    unsigned long long diff = 4;
    
    while (term <= num) {
        if (term == num) {
            return true;
        }
        
        if (ULLONG_MAX - term < diff) {
            break;
        }
        
        term += diff;
        
        if (ULLONG_MAX - diff < 4) {
            break;
        }
        
        diff += 4;
    }
    
    return false;
}

int main(void) {
    unsigned long long testNumbers[] = {0, 1, 5, 9, 13, 17, 21, 100, 101, 102};
    size_t numTests = sizeof(testNumbers) / sizeof(testNumbers[0]);
    
    for (size_t i = 0; i < numTests; i++) {
        if (isInSequence(testNumbers[i])) {
            printf("%llu is in the sequence\n", testNumbers[i]);
        } else {
            printf("%llu is not in the sequence\n", testNumbers[i]);
        }
    }
    
    return 0;
}