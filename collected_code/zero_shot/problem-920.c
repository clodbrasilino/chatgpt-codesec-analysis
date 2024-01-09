#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    bool isEmpty;
} Tuple;

void removeNoneValues(Tuple tuples[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (!tuples[i].isEmpty) {
            tuples[count++] = tuples[i];
        }
    }
    for (int i = count; i < size; i++) {
        Tuple noneTuple;
        noneTuple.isEmpty = true;
        tuples[i] = noneTuple;
    }
}

int main() {
    int size = 5; // replace with actual size of tuple list
    Tuple tuples[size]; // replace with actual tuple list
    // call removeNoneValues function passing the tuple list and size
    removeNoneValues(tuples, size);
    
    // print the modified tuple list
    for (int i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].x, tuples[i].y);
    }
    
    return 0;
}