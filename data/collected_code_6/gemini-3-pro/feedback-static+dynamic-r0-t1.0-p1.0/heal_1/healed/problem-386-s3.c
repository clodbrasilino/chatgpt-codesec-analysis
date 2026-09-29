#include <stdio.h>
#include <stdlib.h>

int minimumSwaps(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int left_brackets = 0;
    int right_brackets = 0;
    int imbalance = 0;
    int swaps = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '[') {
            left_brackets++;
            if (imbalance > 0) {
                swaps += imbalance;
                imbalance--;
            }
        } else if (str[i] == ']') {
            right_brackets++;
            imbalance = right_brackets - left_brackets;
        } else {
            return -1;
        }
    }

    if (left_brackets != right_brackets) {
        return -1;
    }

    return swaps;
}

int main(void) {
    const char *str1 = "[]][][";
    const char *str2 = "[[][]]";
    
    int result1 = minimumSwaps(str1);
    if (result1 != -1) {
        printf("%d\n", result1);
    }

    int result2 = minimumSwaps(str2);
    if (result2 != -1) {
        printf("%d\n", result2);
    }

    return 0;
}