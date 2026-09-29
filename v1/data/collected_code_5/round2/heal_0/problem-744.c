#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_TUPLE 4

int checkNoneValue(int tuple[], int size) {
    int i;
    for(i = 0; i < size; i++) {
        if(tuple[i] == '\0') {
            return 1;
        }
    }
    return 0;
}

int main() {
    int tuple[SIZE_OF_TUPLE] = {1, 2, '\0', 3};

    if(checkNoneValue(tuple, SIZE_OF_TUPLE)) {
        printf("The tuple contains None Value\n");
    }
    else {
        printf("The tuple does not contain None Value\n");
    }

    return 0;
}