#include <stdio.h>
#include <stdlib.h>

int findMaxDifference(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    int current_diff = 0;
    int max_diff = -1;
    int all_ones = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '0') {
            all_ones = 0;
            break;
        }
    }

    if (all_ones) {
        return -1;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        int val = (str[i] == '0') ? 1 : -1;
        
        current_diff += val;
        
        if (max_diff < current_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }

    return max_diff;
}

int main(void) {
    const char *binaryString = "11000010001";
    int maxDiff = findMaxDifference(binaryString);
    
    printf("%d\n", maxDiff);
    
    return 0;
}