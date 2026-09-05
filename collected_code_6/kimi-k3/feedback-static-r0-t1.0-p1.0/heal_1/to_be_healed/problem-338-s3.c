#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    int count = 0;
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'str==NULL' is redundant or there is possible null pointer dereference: str. [nullPointerRedundantCheck]
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