#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple* data;
    int count;
} TupleList;

TupleList extract_symmetric_pairs(TupleList list) {
    TupleList result;
    result.count = 0;
    
    if (list.count <= 0 || list.data == NULL) {
        result.data = NULL;
        return result;
    }
    
    result.data = (Tuple*)malloc(list.count * sizeof(Tuple));
    if (result.data == NULL) {
        result.count = 0;
        return result;
    }
    
    for (int i = 0; i < list.count; i++) {
        if (list.data[i].a == list.data[i].b) {
            result.data[result.count++] = list.data[i];
        }
    }
    
    Tuple* temp = (Tuple*)realloc(result.data, result.count * sizeof(Tuple));
    if (temp != NULL || result.count == 0) {
        result.data = temp;
    }
    
    return result;
}

int main() {
    Tuple data[] = {{1, 1}, {2, 3}, {4, 4}, {5, 6}, {7, 7}};
    TupleList list = {data, 5};
    
    TupleList symmetric = extract_symmetric_pairs(list);
    
    for (int i = 0; i < symmetric.count; i++) {
        printf("(%d, %d)\n", symmetric.data[i].a, symmetric.data[i].b);
    }
    
    free(symmetric.data);
    
    return 0;
}