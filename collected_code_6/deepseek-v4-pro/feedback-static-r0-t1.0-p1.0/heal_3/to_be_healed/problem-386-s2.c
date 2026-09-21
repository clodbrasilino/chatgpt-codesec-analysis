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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        printf("Min swaps for %s: %d\n", strings[i], minSwaps(strings[i], strlen(strings[i])));
    }
    
    return 0;
}