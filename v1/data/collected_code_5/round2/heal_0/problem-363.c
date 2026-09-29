#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void addElements(int *tuple, int size, int k) {
    for(int i=0; i<size; i++) {
        tuple[i] += k;
    }
}

int main() {
    int tuple[SIZE] = {0, 1, 2, 3, 4};
    int k = 5;
    
    addElements(tuple, SIZE, k);

    for(int i=0; i<SIZE; i++) {
        printf("%d ", tuple[i]);
    }
    
    return 0;
}