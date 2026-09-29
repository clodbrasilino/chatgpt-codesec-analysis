#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_SIZE 1001

void removeWordsWithKLength(const char* str, int k) {
    int i, j, wordStart = -1, wordEnd;
    int len = strnlen(str, MAX_SIZE);

    for (i = 0; i <= len && i < MAX_SIZE; i++) {
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
    char str[MAX_SIZE] = {0};
    int k;

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL) {
        if(strchr(str, '\n')) {
            str[strcspn(str, "\n")] = 0; 
        }
    }

    printf("Enter the length of words to remove: ");
    if(scanf("%d", &k) == 1 && k <= INT_MAX && k >= 0) {
        removeWordsWithKLength(str, k);
    }
    
    return 0;
}