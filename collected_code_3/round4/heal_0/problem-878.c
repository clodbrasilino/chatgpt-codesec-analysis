#include <stdio.h>

typedef struct {
    int elements[100];
    int size;
} Tuple;

int checkTupleSize(Tuple tuple, int k) {
    if(tuple.size == k) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    Tuple tuple;
    tuple.size = 5;

    int k = 5;
    int result = checkTupleSize(tuple, k);

    if(result == 1) {
        printf("The tuple contains exactly %d elements.\n", k);
    } else {
        printf("The tuple does not contain exactly %d elements.\n", k);
    }

    return 0;
}