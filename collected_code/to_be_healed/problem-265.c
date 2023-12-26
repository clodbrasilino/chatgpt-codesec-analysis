#include <stdio.h>

void splitList(int list[], int length, int n) {
    int i;
    for(i = 0; i < length; i++) {
        if(i % n == 0) {
            printf("\n");
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d ", list[i]);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(list) / sizeof(list[0]);
    int n = 3;
    
    splitList(list, length, n);
    
    return 0;
}