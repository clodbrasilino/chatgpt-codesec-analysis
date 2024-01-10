#include <stdio.h>

int getItem(int *tuple, int index) {
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    return tuple[index];
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int index = 2;
    int item = getItem(tuple, index);
    printf("Item at index %d is: %d\n", index, item);
    
    return 0;
}