#include <stdio.h>

void extractElements(int **list, int rowSize, int colSize, int *elements, int numElements) {
    for(int i = 0; i < numElements; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'elements[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int element = elements[i];
        int found = 0;

        for(int row = 0; row < rowSize; row++) {
            for(int col = 0; col < colSize; col++) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'list[row][col]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                if(list[row][col] == element) {
                    printf("%d ", element);
                    found = 1;
                }
            }
        }

        if(!found) {
            printf("Element %d not found\n", element);
        }
    }
}

int main() {
    // Example usage:
    
    int list[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int elements[] = {3, 7, 12};
    int numElements = sizeof(elements) / sizeof(elements[0]);
    
    int rowSize = sizeof(list) / sizeof(list[0]);
    int colSize = sizeof(list[0]) / sizeof(list[0][0]);
    
    extractElements((int **)list, rowSize, colSize, elements, numElements);

    return 0;
}