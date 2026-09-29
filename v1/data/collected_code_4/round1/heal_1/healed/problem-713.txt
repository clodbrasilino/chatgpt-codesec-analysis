#include <stdbool.h>
#include <stdlib.h>

#define TUPLE_SIZE 4

bool checkValid(int* tupleItems) {
    if(tupleItems == NULL) {
        return false;
    }

    for(int i = 0; i < TUPLE_SIZE; i++) {
        if(tupleItems[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int* tupleItems = (int *)malloc(TUPLE_SIZE * sizeof(int));

    if(tupleItems == NULL) {
        return -1;
    }

    for(int i = 0; i < TUPLE_SIZE; i++) {
        tupleItems[i] = i + 1;
    }

    if(checkValid(tupleItems)) {
        free(tupleItems);
        return 1;
    } else {
        free(tupleItems);
        return 0;
    }
}