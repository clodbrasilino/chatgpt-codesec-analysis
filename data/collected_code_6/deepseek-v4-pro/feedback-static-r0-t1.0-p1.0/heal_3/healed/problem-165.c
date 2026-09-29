#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_matching_positions(const char *str) {
    int count = 0;
    int i = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (str[i] != '\0') {
        if (i >= 26) {
            break;
        }
        
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if (lower == 'a' + i) {
                count++;
            }
        }
        i++;
    }
    
    return count;
}

int main(void) {
    const char *test1 = "AbC";
    const char *test2 = "abcdefghijklmnopqrstuvwxyz";
    const char *test3 = "ABC";
    const char *test4 = "";
    const char *test5 = NULL;
    
    printf("Test 1: %d\n", count_matching_positions(test1));
    printf("Test 2: %d\n", count_matching_positions(test2));
    printf("Test 3: %d\n", count_matching_positions(test3));
    printf("Test 4: %d\n", count_matching_positions(test4));
    printf("Test 5: %d\n", count_matching_positions(test5));
    
    return 0;
}