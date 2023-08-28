#include <stdio.h>
#include <string.h>

void removeWordsWithKLength(char* str, int k) {
    int i, j, wordStart, wordEnd, len;
    // Initialize wordStart with -1
    wordStart = -1;
    len = strlen(str);
    
    // Iterate through the string
    for (i = 0; i <= len; i++) {
        // If current character is letter or digit
        if (isalnum(str[i])) {
            // If wordStart is -1, set it to the current index
            if (wordStart == -1) {
                wordStart = i;
            }
        } 
        else {
            // If wordStart is not -1, then a word is found
            if (wordStart != -1) {
                wordEnd = i - 1;
                int wordLen = wordEnd - wordStart + 1;
                
                // If word length is not equal to k, print the word
                if (wordLen != k) {
                    for (j = wordStart; j <= wordEnd; j++) {
                        printf("%c", str[j]);
                    }
                    printf(" ");
                }
                wordStart = -1;
            }
        }
    }
}

int main() {
    char str[100];
    int k;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    printf("Enter the length of words to remove: ");
    scanf("%d", &k);
    
    removeWordsWithKLength(str, k);
    
    return 0;
}