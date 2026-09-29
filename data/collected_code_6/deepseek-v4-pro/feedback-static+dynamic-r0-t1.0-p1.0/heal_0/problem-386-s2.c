#include <stdio.h>
#include <string.h>

int minSwaps(char *str) {
    int balance = 0;
    int max_imbalance = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (str[i] == ']') {
            balance--;
        } else {
            balance++;
        }
        
        if (balance < max_imbalance) {
            max_imbalance = balance;
        }
    }
    
    int swaps = (-max_imbalance + 1) / 2;
    return swaps;
}

int main() {
    char str1[] = "[]][][";
    char str2[] = "[[][]]";
    char str3[] = "]]][[[";
    char str4[] = "[]";
    char str5[] = "]][[";
    
    printf("Min swaps for %s: %d\n", str1, minSwaps(str1));
    printf("Min swaps for %s: %d\n", str2, minSwaps(str2));
    printf("Min swaps for %s: %d\n", str3, minSwaps(str3));
    printf("Min swaps for %s: %d\n", str4, minSwaps(str4));
    printf("Min swaps for %s: %d\n", str5, minSwaps(str5));
    
    return 0;
}