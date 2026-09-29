#include <stdio.h>
#include <stdbool.h>

bool canRearrangeAdjacentDifferent(const char* str) {
    int count[26] = {0};
    int len = 0;
  
    while (str[len] != '\0') {
        count[str[len] - 'a']++;
        len++;
    }
    
    for (int i = 0; i < 26; i++) {
        if (count[i] > (len + 1) / 2) {
            return false;
        }
    }
    
    return true;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%100s", str);
    
    if (canRearrangeAdjacentDifferent(str)) {
        printf("The letters of the given string can be rearranged so that two adjacent characters are different.\n");
    } else {
        printf("The letters of the given string cannot be rearranged to satisfy the condition.\n");
    }
    
    return 0;
}
