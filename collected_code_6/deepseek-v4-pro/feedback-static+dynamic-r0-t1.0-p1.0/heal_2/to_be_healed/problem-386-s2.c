#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'str' can be declared as pointer to const [constParameterPointer]
 */
int minSwaps(char *str, size_t max_len) {
    int balance = 0;
    int max_imbalance = 0;
    size_t i = 0;
    
    while (i < max_len && str[i] != '\0') {
        if (str[i] == ']') {
            balance--;
        } else if (str[i] == '[') {
            balance++;
        }
        
        if (balance < max_imbalance) {
            max_imbalance = balance;
        }
        i++;
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
    
    printf("Min swaps for %s: %d\n", str1, minSwaps(str1, sizeof(str1)));
    printf("Min swaps for %s: %d\n", str2, minSwaps(str2, sizeof(str2)));
    printf("Min swaps for %s: %d\n", str3, minSwaps(str3, sizeof(str3)));
    printf("Min swaps for %s: %d\n", str4, minSwaps(str4, sizeof(str4)));
    printf("Min swaps for %s: %d\n", str5, minSwaps(str5, sizeof(str5)));
    
    return 0;
}