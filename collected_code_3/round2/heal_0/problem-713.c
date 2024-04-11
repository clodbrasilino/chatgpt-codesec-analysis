#include <stdio.h>
#include <stdbool.h>

#define TUPLE_SIZE 3

bool checkValidTuple(int tuple[TUPLE_SIZE]) {
    for(int i = 0; i < TUPLE_SIZE; i++) {
        if(tuple[i] < 0 || tuple[i] > 100) {
            return false;
        }
    }
    return true;
}

int main() {
    int tuple[TUPLE_SIZE] = {10, 20, 30};
    if(checkValidTuple(tuple)) {
        printf("The tuple contains all valid values.\n");
    } else {
        printf("The tuple contains invalid values.\n");
    }
    return 0;
}