#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSwaps(char *str) {
    int left = 0, right = 0, swaps = 0, imbalance = 0;
    int i;

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == '[') {
            left++;
            if(imbalance > 0) {
                swaps += imbalance;
                imbalance--;
            }
        } else if(str[i] == ']') {
            right++;
            imbalance = right - left;
        }
    }

    return swaps;
}

int main() {
    char str[] = "[]][][";
    printf("Minimum number of swaps required for bracket balancing is %d", countSwaps(str));
    return 0;
}