#include <stdio.h>

#define SIZE 1000

struct tuple {
    int values[SIZE];
};

void remove_none_tuples(struct tuple tuples[], int * count) {
    int empty;
    for(int i = 0; i < *count; i++) {
        empty = 1;
        for (int j = 0; j < SIZE; j++) {
            if (tuples[i].values[j] != 0) {
                empty = 0;
                break;
            }
        }
        if (empty) {
            for(int j = i; j < (*count) - 1; j++) {
                tuples[j] = tuples[j + 1];
            }
            
            (*count)--;
            i--;
        }
    }
}

int main() {
    struct tuple tuples[SIZE];
    int count = SIZE;

    // Initializing tuples
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tuples[i].values[j] = 0;
        }
    }

    // Adding non-zero tuple
    tuples[SIZE/2].values[SIZE/2] = 1;

    remove_none_tuples(tuples, &count);

    // Printing result
    if (count == 1 && tuples[0].values[SIZE/2] == 1) {
        printf("Successful\n");
    } else {
        printf("Failed\n");
    }

    return 0;
}