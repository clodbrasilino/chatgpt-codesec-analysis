#include <stdio.h>

#define SIZE 3

typedef struct {
    int values[SIZE];
} Tuple;

Tuple subtractTuples(Tuple t1, Tuple t2){
    Tuple result;

    for(int i=0; i<SIZE; i++){
        result.values[i] = t1.values[i] - t2.values[i];
    }

    return result;
}

int main(){
    Tuple t1 = {{1, 2, 3}};
    Tuple t2 = {{4, 5, 6}};
    Tuple result = subtractTuples(t1, t2);

    for(int i=0; i<SIZE; i++){
        printf("%d ", result.values[i]);
    }

    return 0;
}