#include <stdio.h>

struct Tuple {
    int arr[100];
    int size;
};

int checkTupleSize(struct Tuple t, int k) {
    if(t.size == k) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    struct Tuple t;
    t.size = 5;
    int k = 5;

    if(checkTupleSize(t, k)) {
        printf("The tuple contains exactly %d elements.\n", k);
    } else {
        printf("The tuple does not contain exactly %d elements.\n", k);
    }

    return 0;
}