#include <stdio.h>
#include <string.h>

int minSwaps(const char *str, size_t len) {
    int balance = 0;
    int max_imbalance = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ']') {
            balance--;
        } else if (str[i] == '[') {
            balance++;
        }
        
        if (balance < max_imbalance) {
            max_imbalance = balance;
        }
    }
    
    int swaps = (-max_imbalance + 1) / 2;
    return swaps;
}

int main(void) {
    const char *strings[] = {"[]][][", "[[][]]", "]]][[[", "[]", "]][["};
    size_t num_strings = sizeof(strings) / sizeof(strings[0]);
    
    for (size_t i = 0; i < num_strings; i++) {
        size_t len = 0;
        while (strings[i][len] != '\0') {
            len++;
        }
        printf("Min swaps for %s: %d\n", strings[i], minSwaps(strings[i], len));
    }
    
    return 0;
}