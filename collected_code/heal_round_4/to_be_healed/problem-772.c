#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

void removeWordsWithKLength(const char* str, int k) {
    int i, j, wordStart = -1, wordEnd, len;
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    len = strlen(str);

    for (i = 0; i <= len; i++) {
        if (isalnum((unsigned char)str[i])) {
            if (wordStart == -1) {
                wordStart = i;
            }
        } 
        else {
            if(wordStart != -1)
            {
                wordEnd = i - 1;
                int wordLen = wordEnd - wordStart + 1;
                
                if(wordLen != k) {
                    for(j = wordStart; j <= wordEnd; j++) {
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];
    int k;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    if(strchr(str, '\n')) {
        str[strcspn(str, "\n")] = 0; 
    }

    printf("Enter the length of words to remove: ");
    if(scanf("%d", &k) == 1 && k <= MAX_SIZE){
        removeWordsWithKLength(str, k);
    }
    
    return 0;
}