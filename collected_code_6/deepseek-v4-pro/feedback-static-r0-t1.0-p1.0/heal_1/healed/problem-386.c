#include <stdio.h>
#include <string.h>

int min_swaps_for_balance(char *str, size_t len) {
    int balance = 0;
    int swaps = 0;
    size_t left = 0;
    size_t right = len - 1;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            balance++;
        } else {
            balance--;
        }
        
        if (balance < 0) {
            while (left < right && str[left] != ']') {
                left++;
            }
            while (right > left && str[right] != '[') {
                right--;
            }
            
            if (left < right) {
                char temp = str[left];
                str[left] = str[right];
                str[right] = temp;
                swaps++;
                balance = 1;
                left++;
                right--;
            }
        }
    }
    
    return swaps;
}

int main(void) {
    char str1[] = "[]][][";
    char str2[] = "[[][]]";
    char str3[] = "]][[";
    
    printf("String: %s, Min swaps: %d\n", str1, min_swaps_for_balance(str1, strlen(str1)));
    printf("String: %s, Min swaps: %d\n", str2, min_swaps_for_balance(str2, strlen(str2)));
    printf("String: %s, Min swaps: %d\n", str3, min_swaps_for_balance(str3, strlen(str3)));
    
    return 0;
}