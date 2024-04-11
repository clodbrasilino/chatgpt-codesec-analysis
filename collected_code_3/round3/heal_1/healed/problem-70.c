#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *arr;
    int length;
};

int checkEqualLength(struct Tuple *tuples, int n) {
    int length = tuples[0].length;
    for (int i = 1; i < n; i++) {
        if (tuples[i].length != length) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n = 3;
    struct Tuple *tuples = malloc(n * sizeof(struct Tuple));
    if(tuples == NULL){
        return -1;
    }
    for (int i = 0; i < n; i++) {
        tuples[i].length = 5;
        tuples[i].arr = malloc(tuples[i].length * sizeof(int));
        if(tuples[i].arr == NULL){
            free(tuples);
            return -1;
        }
    }
    printf("%s\n", checkEqualLength(tuples, n) ? "Equal" : "Not Equal");
    for (int i = 0; i < n; i++) {
        free(tuples[i].arr);
    }
    free(tuples);
    return 0;
}