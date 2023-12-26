#include <stdio.h>

void sortList(char list[], int size) {
    int i, j;
    char temp;
    
    for (i = 1; i < size; i++) {
        j = i;
        
        /* Possible weaknesses found:
         *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list[j-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (j > 0 && list[j-1] > list[j]) {
            temp = list[j];
            list[j] = list[j-1];
            list[j-1] = temp;
            j--;
        }
    }
}

int main() {
    char list[] = {'z', 'a', 'b', 'c'};
    int size = sizeof(list) / sizeof(list[0]);
    
    sortList(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%c ", list[i]);
    }
    
    return 0;
}