#include<stdio.h>

void extractTuples(int tuple1[], int tuple2[], int result[], int size) {
    for(int i = 0; i < size; i++) {
        result[i] = tuple1[i] & tuple2[i];
    }
}

int main() {
    // Example usage
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {2, 3, 4};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    int result[size];

    extractTuples(tuple1, tuple2, result, size);

    // Print the resulting tuple
    for(int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    
    return 0;
}