#include <stdio.h>
#include <stdbool.h>

#define TUPLE_SIZE 5

bool checkNone(int tuple[], int size) {
    for(int i = 0; i < size; i++) {
        if(tuple[i] == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int tuple[TUPLE_SIZE] = {1, 2, 3, 4, 0};
    if(checkNone(tuple, TUPLE_SIZE)) {
        printf("Tuple has none value.\n");
    } else {
        printf("Tuple has no none value.\n");
    }
    return 0;
}