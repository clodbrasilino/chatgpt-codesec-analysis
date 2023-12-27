#include<stdio.h>

void extractTuples(const int* tuple1, const int* tuple2, int* result, int size) {
    for(int i = 0; i < size; i++) {
        result[i] = tuple1[i] & tuple2[i];
    }
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {2, 3, 4};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    int result[size];

    extractTuples(tuple1, tuple2, result, size);

    for(int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    
    return 0;
}