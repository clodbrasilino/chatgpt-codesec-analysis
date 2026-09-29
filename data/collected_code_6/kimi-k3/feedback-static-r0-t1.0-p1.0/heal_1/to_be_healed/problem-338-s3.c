#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    int count = 0;
    /* Possible weaknesses found:
     *  Either the condition 'str==NULL' is redundant or there is possible null pointer dereference: str. [nullPointerRedundantCheck]
     *  Null pointer dereference
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    
    /* Possible weaknesses found:
     *  Assuming that condition 'str==NULL' is not redundant
     */
    if (str == NULL) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        int result = countSubstrings(str);
        printf("Number of substrings with same first and last characters: %d\n", result);
    } else {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    return 0;
}