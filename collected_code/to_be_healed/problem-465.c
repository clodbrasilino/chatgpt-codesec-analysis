#include <stdio.h>
#include <string.h>

void dropEmptyItems(char* dict[]) {
    int i, j;
    /* Possible weaknesses found:
     *  Cannot determine that 'dict[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for(i = 0; dict[i] != NULL; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'dict[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if(strlen(dict[i]) == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dict[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            for(j = i; dict[j] != NULL; j++) {
                dict[j] = dict[j+1];
            }
            i--; // Adjust i to recheck the current position
        }
    }
}

int main() {
    char* dict[] = {"apple", "", "banana", "carrot", "", "date", NULL};
    int i;
    
    printf("Before dropping empty items:\n");
    for(i = 0; dict[i] != NULL; i++) {
        printf("%s\n", dict[i]);
    }
    
    dropEmptyItems(dict);
    
    printf("\nAfter dropping empty items:\n");
    for(i = 0; dict[i] != NULL; i++) {
        printf("%s\n", dict[i]);
    }
    
    return 0;
}