#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 200

int getLengthOfLongestWord(const char* str) {
    int maxLength = 0;
    int length = 0;
    int i = 0;

    while(str[i] != '\0') {
        if (str[i] != ' ') {
            length++;
        } else {
            if (length > maxLength) {
                maxLength = length;
            }
            length = 0;
        }
        i++;
    }

    if (length > maxLength) {
        maxLength = length;
    }

    return maxLength;
}

int main() {
    char* str = (char*)malloc(MAX_SIZE * sizeof(char));

    printf("Enter a sentence: ");
    if(fgets(str, MAX_SIZE, stdin) != NULL) {
        /* Possible weaknesses found:
         *  use of possibly-NULL 'str' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
         */
        str[strcspn(str, "\n")] = '\0';
        int length = getLengthOfLongestWord(str);
        printf("Length of the longest word is %d\n", length);
    }

    free(str);
    return 0;
}