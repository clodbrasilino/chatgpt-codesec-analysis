#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int z;
} Tuple;

bool checkValidTuple(Tuple t) {
    if(t.x >= 0 && t.y >= 0 && t.z >= 0) {
        return true;
    }
    return false;
}

int main() {
    Tuple t1 = {1, 2, 3};
    Tuple t2 = {-1, 2, 3};

    if(checkValidTuple(t1)) {
        printf("Tuple t1 is valid.\n");
    } else {
        printf("Tuple t1 is not valid.\n");
    }

    if(checkValidTuple(t2)) {
        printf("Tuple t2 is valid.\n");
    } else {
        printf("Tuple t2 is not valid.\n");
    }

    return 0;
}