#include <stdio.h>
#include <stdbool.h>

void filterDictionary(int dictionary[], int size, int value) {
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(dictionary[i] == value) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d\n", dictionary[i]);
        }
    }
}