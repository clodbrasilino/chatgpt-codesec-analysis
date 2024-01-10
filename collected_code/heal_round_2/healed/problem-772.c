#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

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
    char str[MAX_SIZE];
    int k;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    if (strchr(str, '\n')) {
        str[strcspn(str, "\n")] = 0; 
    }

    printf("Enter the length of words to remove: ");
    if(scanf("%d", &k) == 1){
        removeWordsWithKLength(str, k);
    }
    
    return 0;
}