#include <stdio.h>

void cubeElements(int *list, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        list[i] = list[i] * list[i] * list[i];
    }
}

int main() {
    int size;
    printf("Enter the size of the list: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'size' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &size);
    
    int list[size];
    printf("Enter the elements of the list: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &list[i]);
    }
    
    cubeElements(list, size);
    
    printf("Cubes of individual elements in the list:\n");
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d\n", list[i]);
    }
    
    return 0;
}