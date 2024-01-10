#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeWordsWithKLength(const char* str, int k) {
    int i, j, wordStart = -1, wordEnd, len;

    len = strlen(str);

    for (i = 0; i <= len; i++) {
        if (isalnum((unsigned char)str[i])) {
            if (wordStart == -1) {
                wordStart = i;
            }
        } 
        else {
            if (wordStart != -1) {
                wordEnd = i - 1;
                int wordLen = wordEnd - wordStart + 1;
                
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
    char str[1000];
    int k;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = 0; //removing newline character

    printf("Enter the length of words to remove: ");
    scanf("%d", &k);
    
    removeWordsWithKLength(str, k);
    
    return 0;
}