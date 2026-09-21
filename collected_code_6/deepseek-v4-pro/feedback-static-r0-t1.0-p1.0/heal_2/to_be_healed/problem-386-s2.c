#include <stdio.h>
#include <string.h>

int minSwaps(const char *str, size_t len) {
    int balance = 0;
    int max_imbalance = 0;
    
    for (size_t i = 0; i < len; i++) {
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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Min swaps for %s: %d\n", str1, minSwaps(str1, strlen(str1)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Min swaps for %s: %d\n", str2, minSwaps(str2, strlen(str2)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Min swaps for %s: %d\n", str3, minSwaps(str3, strlen(str3)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Min swaps for %s: %d\n", str4, minSwaps(str4, strlen(str4)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Min swaps for %s: %d\n", str5, minSwaps(str5, strlen(str5)));
    
    return 0;
}