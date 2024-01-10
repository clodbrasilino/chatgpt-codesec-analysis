#include <stdio.h>

void shiftLastToFirst(int list[], int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'list[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int last = list[size-1];

    for(int i=size-1; i>0; i--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        list[i] = list[i-1];
    }

    list[0] = last;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    
    shiftLastToFirst(list, size);
    
    for(int i=0; i<size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}