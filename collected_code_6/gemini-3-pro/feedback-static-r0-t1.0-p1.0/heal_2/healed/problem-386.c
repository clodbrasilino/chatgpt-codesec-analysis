#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char* s) {
    if (s == NULL) {
        return -1;
    }

    int left = 0;
    int right = 0;
    int swap = 0;
    int imbalance = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '[') {
            left++;
            if (imbalance > 0) {
                swap += imbalance;
                imbalance--;
            }
        } else if (s[i] == ']') {
            right++;
            imbalance = right - left;
        } else {
            return -1; 
        }
    }

    if (left != right) {
        return -1;
    }

    return swap;
}

int main() {
    const char str1[] = "[]][][";
    const char str2[] = "[[][]]";
    const char str3[] = "][][][";
    
    int swaps1 = minSwaps(str1);
    int swaps2 = minSwaps(str2);
    int swaps3 = minSwaps(str3);
    
    if (swaps1 != -1) {
        printf("%d\n", swaps1);
    }
    
    if (swaps2 != -1) {
        printf("%d\n", swaps2);
    }
    
    if (swaps3 != -1) {
        printf("%d\n", swaps3);
    }
    
    return 0;
}