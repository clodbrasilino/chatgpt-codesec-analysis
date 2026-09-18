#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* extract_nth(Tuple* tuples, int size, int n){
    if(n < 0 || n >= size) {
        return NULL;
    }
    Tuple* tmp = (Tuple*)malloc(sizeof(Tuple));
    if (tmp == NULL){
        return NULL;
    }
    *tmp = tuples[n];
    return tmp;
}

int main() {
    int n = 3;
    Tuple tuples[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    int size = sizeof(tuples) / sizeof(tuples[0]);
    Tuple* nth = extract_nth(tuples, size, n);
    if(nth == NULL){
        printf("Invalid index or failed to allocate memory\n");
        return 1;
    }
    printf("The nth tuple is (%d, %d)\n", nth->first, nth->second);
    free(nth);
    return 0;
}
