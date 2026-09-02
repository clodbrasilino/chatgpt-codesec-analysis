#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
} Tuple;

bool isSubset(const Tuple *smaller, const Tuple *larger) {
    for (int i = 0; i < smaller->size; ++i) {
        bool found = false;
        for (int j = 0; j < larger->size; ++j) {
            if (smaller->data[i] == larger->data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {1, 2, 3, 4, 5};

    Tuple tuple1 = {data1, 3};
    Tuple tuple2 = {data2, 5};

    if (isSubset(&tuple1, &tuple2)) {
        printf("Tuple1 is a subset of Tuple2\n");
    } else {
        printf("Tuple1 is not a subset of Tuple2\n");
    }

    return 0;
}