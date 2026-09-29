#include<stdio.h>
#include<string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* reverseString(char* string) {
    int len = strlen(string);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char* reverse = (char*)malloc(sizeof(char)*(len+1));

    for(int i = 0; i<len; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'reverse' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        reverse[i] = string[len-1-i];
    }
    reverse[len] = '\0';
    
    return reverse;
}

int countReversePairs(char** list, int count) {
    int reversePairCount = 0;
    for(int i = 0; i < count; i++) {
        for(int j = i+1; j < count; j++) {
            char* reverse = reverseString(list[i]);
            /* Possible weaknesses found:
             *  use of possibly-NULL 'reverse' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
             */
            if(strcmp(reverse, list[j]) == 0) {
                reversePairCount++;
            }
            /* Possible weaknesses found:
             *  include '<stdlib.h>' or provide a declaration of 'free'
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
             */
            free(reverse);
        }
    }
    return reversePairCount;
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);
    
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    char** list = (char**)malloc(sizeof(char*)*n);
    for(int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list[i] = (char*)malloc(sizeof(char)*100);
    }

    printf("Enter the strings: \n");
    for(int i = 0; i < n; ++i) {
        scanf("%s", list[i]);
    }

    int result = countReversePairs(list, n);
    printf("Number of reverse pairs: %d\n", result);
    
    for(int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         */
        free(list[i]);
    }
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(list);

    return 0;
    
}