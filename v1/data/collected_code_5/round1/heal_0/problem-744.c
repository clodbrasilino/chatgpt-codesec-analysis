#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *first;
    int *second;
}Tuple;

int checkNoneInTuple(Tuple tuple){
    if(tuple.first == NULL || tuple.second == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    int a = 5;
    int b = 10;
    Tuple tuple1;
    tuple1.first = &a;
    tuple1.second = &b;
    
    Tuple tuple2;
    tuple2.first = NULL;
    tuple2.second = &b;
    
    if(checkNoneInTuple(tuple1)){
        printf("tuple1 has NULL value\n");
    }
    else{
        printf("No NULL values in tuple1\n");
    }
    
    if(checkNoneInTuple(tuple2)){
        printf("tuple2 has NULL value\n");
    }
    else{
        printf("No NULL values in tuple2\n");
    }
    
    return 0;
}